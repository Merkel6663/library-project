class Book:
    def __init__(self, id, title, author, year, pages, genre, is_read,reviews):
        self.__id = id
        self.title = title
        self.author = author
        self.year = year
        self.pages = pages
        self.genre = genre
        self.__is_read = is_read
        self.rating = None
        self.reviews = reviews

    def change_read_status(self):
        if self.__is_read == True:
            self.__is_read = False
        else: 
            self.__is_read == True

    def add_review(self, rating, review):
        if self.rating == None:
            self.rating = [rating]
        else:
            self.rating.append(rating)
        if not self.reviews:
            self.reviews = [review]
        else:
            self.reviews.append(review)

    def __str__(self):
        print("Информация о книге:\n")
        print("="*max(len(f"Название: {self.title}"),len(f"Автор: {self.author}"),len(f"Год выпуска: {self.year}"),len(f"Количество страниц: {self.pages}"),len(f"Жанр: {self.genre}"),len("Статус: не прочитана")))
        print(f"Название: {self.title}")
        print(f"Автор: {self.author}")
        print(f"Год выпуска: {self.year}")
        print(f"Количество страниц: {self.pages}")
        print(f"Жанр: {self.genre}")
        if self.__is_read:
            print("Статус: прочитана")
        else:
            print("Статус: не прочитана")
        