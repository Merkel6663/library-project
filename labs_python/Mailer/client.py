import socket
import json
import sys

class MailClient():
    def __init__(self, host: str = '127.0.0.1', port: int = 50007):
        self.host = host
        self.port = port
        self.server_address = (host, port)

    def get_user_input(self):
        while True:
            try:
                email = input("Input email recipient: ").strip()
                
                print("\nInput message(double tap Enter to finish):")
                lines = []
                empty_lines = 0
                
                while True:
                    try:
                        line = input()
                        if line == "":
                            empty_lines += 1
                            if empty_lines >= 2:
                                break
                        else:
                            empty_lines = 0
                            lines.append(line)
                    except EOFError:
                        break
                
                message = "\n".join(lines).strip()
                
                return email, message
                
            except KeyboardInterrupt:
                print("\n\nInput interrupted. Stopping client.")
                sys.exit(0)
            except Exception as e:
                print(f"Input error: {e}")
                continue
    
    def send_to_server(self, email: str, message: str) -> str:
        try:
            data = json.dumps({
                'email': email,
                'message': message
            })
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
                client_socket.settimeout(10)
                client_socket.connect(self.server_address)
                client_socket.sendall(data.encode('utf-8'))

                response = client_socket.recv(4096).decode('utf-8').strip()
                
                return response
                
        except socket.timeout:
            return "ERROR: Timeout connection"
        except ConnectionRefusedError:
            return "ERROR: Failed to connect to server"
        except socket.error as e:
            return f"ERROR: Network error: {e}"
        except Exception as e:
            return f"ERROR: Unexpected error: {e}"
        
    def parse_server_response(self, response: str, words_email: int) -> tuple:
        if response.startswith('OK'):
            parts = response.split(':')
            if len(parts) > 1:
                ticket_id = parts[1].strip()
                return True, f"Message was successfully sent! Words in email: {words_email} Ticket ID: {ticket_id}", ticket_id
            else:
                return True, "Message was successfully sent!", None
        elif response.startswith('ERROR'):
            error_msg = response[6:] if len(response) > 6 else response
            return False, f"ERROR: {error_msg}", None
        else:
            return False, f"Unexpected server responce: {response}", None
        
    def run(self):
        print("Mailer Client")
        print(f"Connecting to server: {self.host}:{self.port}")
        print("-" * 50)
        
        while True:
            try:
                email, message = self.get_user_input()
                words_email = len(message)
                print("\n" + "=" * 50)
                print("\nSending data to the server...")
                response = self.send_to_server(email, message)
                success, message, ticket_id = self.parse_server_response(response, words_email)
                
                print(f"\nServer responce: {message}")
                
                if success:
                    if ticket_id:
                        print(f"Ticket ID: {ticket_id}")
                    print("-" * 50 + "\n")
                    
                    again = input("Send another message? (y/n): ").strip().lower()
                    if again != 'y':
                        print("Stopping client.")
                        break
                else:
                    print("\n" + "=" * 50)
                    print("SENDING ERROR")
                    print("=" * 50)
                    retry = input("Wuold you try one more time? (y/n): ").strip().lower()
                    if retry != 'y':
                        print("Stopping client.")
                        break
                
                print()
                
            except KeyboardInterrupt:
                print("\n\nClient was stopped by user.")
                break
            except Exception as e:
                print(f"\nCritical error: {e}")
                retry = input("Wuold you try one more time? (y/n): ").strip().lower()
                if retry != 'y':
                    print("Stopping client.")
                    break
def main():
    host = '127.0.0.1'
    port = 50007
    
    try:
        client = MailClient(host=host, port=port)
        client.run()
    except Exception as e:
        print(f"Ошибка: {e}")
        return 1
    return 0

if __name__ == "__main__":
    exit(main())