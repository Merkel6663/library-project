import socket
import configparser
import logging
import re
import uuid
import smtplib
from email.message import EmailMessage
from datetime import datetime
import json

class MailServer:
    def __init__(self, config_path: str ='/Users/maxim2720icloud.com/Documents/VS Code Folder/labs_python/Mailer/config.ini'):
        self.config = self._load_config(config_path)
        self._setup_logging()
        self.host = '127.0.0.1'
        self.port = 50007
        self.running = False

    def _load_config(self, config_path: str):
        config = configparser.ConfigParser()
        try:
            config.read(config_path, encoding='utf-8')
            if 'EMAIL' not in config:
                raise ValueError('Missing EMAIL section in config file')
        except Exception as e:
            print(f"Error loading config: {e}")
            raise
        return config
    
    def _setup_logging(self):
        logging.basicConfig(
            level = logging.INFO,
            format = '%(asctime)s - %(levelname)s - %(message)s',
            datefmt = '%Y-%m-%d %H:%M:%S',
            handlers=[logging.StreamHandler()]
        )
        self.logger = logging.getLogger(__name__)

    def validate_adress(self, email_adress: str) -> bool:
        pattern = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
        return bool(re.match(pattern, email_adress))
    
    def validate_message(self, message: str) -> tuple[bool, str]:
        if not message or message.isspace():
            return False, "Сообщение не может быть пустым"
        else:
            return True, ""

    def generate_ticket_id(self) -> str:
        return str(uuid.uuid4().int)[:5]
    
    def send_message(self, email_adress: str, ticket_id: str, message: str) -> tuple[bool, str]:
        try:
            email_login = self.config['EMAIL']['EMAIL_LOGIN']
            email_password = self.config['EMAIL']['EMAIL_PASSWORD']
            smtp_host = self.config['EMAIL']['SMTP_HOST']
            smtp_port = int(self.config['EMAIL']['SMTP_PORT'])

            subject = f"[Ticket #{ticket_id}] Mailer"

            msg_to_user = EmailMessage()
            msg_to_user['Subject'] = subject
            msg_to_user['From'] = email_login
            msg_to_user['To'] = email_adress
            msg_to_user.set_content(message)

            
            msg_to_admin = EmailMessage()
            msg_to_admin['Subject'] = subject
            msg_to_admin['From'] = email_login
            msg_to_admin['To'] = email_login
            msg_to_admin.set_content(
                f"Sent to: {email_adress}\n"
                f"Date: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n"
                f"Message:\n{message}"
            )

            with smtplib.SMTP_SSL(smtp_host, smtp_port) as server:
                server.login(email_login, email_password)
                server.send_message(msg_to_user)
                server.send_message(msg_to_admin)
            self.logger.info(f'Emails were sent, Ticket#{ticket_id}')
            return True, ""
     
        except smtplib.SMTPAuthenticationError:
            self.logger.error("Authentication error: Unable to login to SMTP server")
            return False, 'Authentication error: Unable to login to SMTP server'
        except smtplib.SMTPException as e:
            self.logger.error(f"Error: {e}")
            return False, f"Error: {e}"
        except Exception as e:
            self.logger.error(f"Unexpected error: {e}")
            return False, f"Unexpected error: {e}"
        
    
    def receive_data(self, conn: socket.socket) -> str:
        data = b""
        try:
            while True:
                chunk = conn.recv(4096)
                if not chunk:
                    break
                data += chunk
                if len(chunk) < 4096:
                    break
        except socket.timeout:
            self.logger.warning("Timeout error")
        except Exception as e:
            self.logger.error(f"ERROR: {e}")
        
        return data.decode('utf-8', errors='ignore').strip()
        
    def handle_client(self, conn: socket.socket, addr: tuple[str, int]):
        client_ip = f"{addr[0]}:{addr[1]}"
        self.logger.info(f"New connection: {client_ip}")

        try:
            data = self.receive_data(conn)
            if not data:
                conn.send(f'Error: no data'.encode('utf-8'))
                self.logger.error(f'Error: no data from client {client_ip}')
                return
            
            try:
                request_data = json.loads(data)
                user_email = request_data.get('email', '').strip()
                user_msg = request_data.get('message', '').strip()
            except json.JSONDecodeError:
                conn.send('ERROR: wrong data form. Waiting for JSON'.encode('utf-8'))
                self.logger.error(f'ERROR: wrong data form from {client_ip}')
                return
            
            if not self.validate_adress(user_email):
                conn.send(f'ERROR: wrong email address'.encode('utf-8'))
                self.logger.error(f'ERROR: wrong email address from {client_ip} : {user_email}')
                return
            

            msg_bool, err_type = self.validate_message(user_msg)
            if not msg_bool:
                conn.send('ERROR: invalid message form'.encode('utf-8'))
                self.longer.error(f'ERROR: invalid message form from {client_ip} : {err_type} ')
                return
            
            ticket_id = self.generate_ticket_id()

            success, send_err = self.send_message(user_email,ticket_id, user_msg)

            if success:
                conn.send(f'OK. Ticket_id: {ticket_id}'.encode('utf-8'))
                self.logger.info(f'Ticket#{ticket_id} was successfully sent')
            else:
                conn.send(f'ERROR: {send_err}'.encode('utf-8'))
                self.logger.error(f'ERROR: Ticket#{ticket_id} : {send_err}')

        except socket.error as e:
            self.logger.error(f'ERROR: error with socket: {e}')
        except Exception as e:
            self.logger.error(f'ERROR: unexpected error: {e}')
        finally:
            conn.close()

    def run(self):
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
                server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
                server_socket.bind((self.host, self.port))
                server_socket.listen(5)

                self.running = True
                print("=" * 50)
                print("MAILER SERVER")
                print("=" * 50)
                print(f"Сервер запущен на {self.host}:{self.port}")
                print("Ожидание подключений...")
                print("Для остановки нажмите Ctrl+C")
                print("-" * 50)

                while self.running:
                    try:
                        conn, addr = server_socket.accept()
                        self.handle_client(conn, addr)
                    except KeyboardInterrupt:
                        self.logger.info('Connection was interrupted')
                        break
                    except Exception as e:
                        self.logger.error(f'ERROR: unexpected error: {e}')
                        continue
        except socket.error as e:
            self.logger.error(f'ERROR: socket error: {e}')

def main():
    try:
        server = MailServer()
        server.run()
    except KeyboardInterrupt:
        print('Server was stopped')
    except Exception as e:
        print(f'ERROR: {e}')
        return 1
    return 0

if __name__ == "__main__":
    exit(main())