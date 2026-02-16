import socket


while True:
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(("localhost", 12345))
    email = input("Введите email-адрес куда нужно отправить сообщение: ")
    message = input("Введите сообщение, которое отправляется на почту: ")
    emmes = f"{email}|{message}"
    l = len(emmes)
    client.send(str(l).encode("utf-8"))
    client.send(emmes.encode("utf-8"))
    response = client.recv(1024).decode("utf-8")
    if response == "OK":
        print(f"Ответ от сервера: {response}")
        client.close()
        break
    else:
        print("Данные введены неправильно, введите снова!!")
