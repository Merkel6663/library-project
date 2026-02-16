import imaplib
import email
import configparser
import time
import re
import logging
from datetime import datetime

class MailCollector:
    def __init__(self, config_path: str = 'config.ini'):
        self.config = self._load_config(config_path)
        self.period = int(self.config['EMAIL']['PERIOD_CHECK'])
        self.running = False
        
    def _load_config(self, config_path: str):
        config = configparser.ConfigParser()
        config.read(config_path, encoding='utf-8')
        return config
    
    def extract_ticket_id(self, subject: str):
        pattern = r'\[Ticket\s+#(\d+)\]\s+Mailer'
        match = re.search(pattern, subject)
        return match.group(1) if match else None
    
    def parse_email(self, msg):
        subject = msg.get('Subject', '')
        from_email = msg.get('From', '')
        
        text = ""
        if msg.is_multipart():
            for part in msg.walk():
                if part.get_content_type() == "text/plain":
                    text = part.get_payload(decode=True).decode('utf-8', errors='ignore')
                    break
        else:
            text = msg.get_payload(decode=True).decode('utf-8', errors='ignore')
        
        return subject, from_email, text.strip()
    
    def log_success(self, ticket_id: str, message: str):
        timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        log_entry = f"TICKET: {ticket_id} | TIME: {timestamp} | MESSAGE: {message[:200]}"
        
        with open('success_request.log', 'a', encoding='utf-8') as f:
            f.write(log_entry + '\n')
        
        print(f"[SUCCESS] Ticket {ticket_id} logged")
    
    def log_error(self, subject: str, message: str):
        timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        log_entry = f"TIME: {timestamp} | SUBJECT: {subject[:100]} | MESSAGE: {message[:200]}"
        
        with open('error_request.log', 'a', encoding='utf-8') as f:
            f.write(log_entry + '\n')
        
        print(f"[ERROR] Logged: {subject[:50]}")
    
    def check_messages(self):
        try:
            imap_host = self.config['EMAIL']['IMAP_HOST']
            imap_port = int(self.config['EMAIL']['IMAP_PORT'])
            email_login = self.config['EMAIL']['EMAIL_LOGIN']
            email_password = self.config['EMAIL']['EMAIL_PASSWORD']
            
            with imaplib.IMAP4_SSL(imap_host, imap_port) as mail:
                mail.login(email_login, email_password)
                mail.select('INBOX')
                
                status, messages = mail.search(None, 'UNSEEN')
                
                if status != 'OK':
                    print("Finding letter error")
                    return
                
                email_ids = messages[0].split()
                if email_ids:
                    print(f"Found new letters: {len(email_ids)}")
                
                for email_id in email_ids:
                    try:
                        status, msg_data = mail.fetch(email_id, '(RFC822)')
                        
                        if status != 'OK':
                            continue
                        
                        raw_email = msg_data[0][1]
                        msg = email.message_from_bytes(raw_email)
                        
                        subject, from_email, text = self.parse_email(msg)
                        
                        ticket_id = self.extract_ticket_id(subject)
                        
                        if ticket_id:
                            self.log_success(ticket_id, text)
                        else:
                            self.log_error(subject, text)
                        
                        mail.store(email_id, '+FLAGS', '\\Seen')
                        
                    except Exception as e:
                        print(f"Parsing error: {e}")
                        continue
                        
        except Exception as e:
            print(f"ERROR: {e}")
    
    def run(self):
        self.running = True
        print("Collector started")
        print(f"Check every {self.period} second(s)")
        print("Ctrl+C for sending")
        
        try:
            while self.running:
                print("\nCheck mail...")
                self.check_messages()
                time.sleep(self.period)
                
        except KeyboardInterrupt:
            print("\nCollector stopped")
        except Exception as e:
            print(f"Critical error: {e}")

def main():
    try:
        collector = MailCollector()
        collector.run()
    except Exception as e:
        print(f"ERROR: {e}")
        return 1
    return 0

if __name__ == "__main__":
    exit(main())