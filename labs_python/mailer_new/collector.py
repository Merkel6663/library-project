import configparser
import imaplib
import email
import re
from time import *
from datetime import *

config = configparser.ConfigParser()
config.read("config.ini")

def log_success(ticket_id, message):
    with open('success_request.log', 'a',encoding='utf-8') as f:
        f.write(f"{datetime.now()} - ID: {ticket_id} - {message}\n")


def collector():
    imap_host = config['EMAIL']['IMAP_HOST']
    imap_port = int(config['EMAIL']['IMAP_PORT'])
    email_admin = config["EMAIL"]["EMAIL_LOGIN"]
    pas_admin = config["EMAIL"]["EMAIL_PASSWORD"]
    mail = imaplib.IMAP4_SSL(imap_host, imap_port)
    mail.login(email_admin, pas_admin)
    mail.select('inbox')
    status, messages = mail.search(None, 'UNSEEN')
    email_ids = messages[0].split()
    for eid in email_ids:
        _, data = mail.fetch(eid, "(RFC822)")
        msg = email.message_from_bytes(data[0][1])
        subject = msg["subject"]
        text = ""
        if msg.is_multipart():
            for part in msg.walk():
                if part.get_content_type() == "text/plain":
                    text = part.get_payload(decode=True).decode("utf-8")
        if re.match(r"^\[Ticket #(\d+)\] Mailer", subject):
            log_success(subject[9:14], text)
        mail.store(eid, '+FLAGS', '\\Seen')
    mail.close()
    mail.logout()


period_check = int(config["EMAIL"]["PERIOD_CHECK"])
while True:
    collector()
    sleep(period_check)