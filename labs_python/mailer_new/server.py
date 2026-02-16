import socket
import configparser
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from datetime import *
import time
import re


def log_error(message):
    with open('error_request.log',"a", encoding='utf-8') as f:
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        f.write(f"{timestamp} ERROR server.py - Ошибка отправления сообщения: {message}\n")

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(("localhost",12345))
server.listen(1)
print("Сервер запущен. Ожидание подключений...")
pattern = r'^[a-zA-Z0-9_.+-]+@(gmail\.com|mail\.ru|ya\.ru)$'
config = configparser.ConfigParser()
config.read("config.ini")
smtp_server = config["EMAIL"]["SMTP_HOST"]
smtp_port = int(config["EMAIL"]["SMTP_PORT"])
while True:
    client,addr = server.accept()
    print(f"Подключен клиент: {addr}")
    l = client.recv(1024).decode("utf-8")
    data = client.recv(int(l)).decode("utf-8")
    ticket_id = hash(data) % 100000
    email,message = data.split("|")
    if re.match(pattern,email):
        print(f"Получено от клиента: {email} {message}")
        msg = MIMEMultipart()
        msg['From'] = config["EMAIL"]["EMAIL_LOGIN"]
        msg['To'] = email
        msg['Subject'] = f"[Ticket #{ticket_id}] Mailer"
        msg.attach(MIMEText(message, 'plain'))
        with smtplib.SMTP(smtp_server, smtp_port, timeout=10) as s:
            s.starttls()
            s.login(config["EMAIL"]["EMAIL_LOGIN"], config["EMAIL"]["EMAIL_PASSWORD"])
            time.sleep(3)
            s.send_message(msg, to_addrs=config["EMAIL"]["EMAIL_LOGIN"])
            s.send_message(msg)
        client.send("OK".encode("utf-8"))
        client.close()
        server.close()
        break
    else:
        client.send("NotOK".encode("utf-8"))
        log_error(message)
        client.close()
        continue