class Book:
    def __init__(self, id, title, author, year, pages, genre, is_read,reviews):
        self.__id = id
        self.title = title
        self.author = author
        self.year = year
        self.pages = pages
        self.genre = genre
        self.__is_read = False
        self.rating = None
        self.reviews = []


    @property
    def id(self):
        return self.__id
    
    @property
    def is_read(self):
        return self.__is_read
    
    def mark_as_read(self):
        self.__is_read = True

    def add_review(self, rating, review):
        if not self.is_read:
            raise ValueError("Нельзя оставить отзыв к непрочитанной книге!")
        if self.rating == None:
            self.rating = [rating]
        else:
            self.rating.append(rating)
        if not self.reviews:
            self.reviews = [review]
        else:
            self.reviews.append(review)

    def __str__(self):

        status = "Прочитана✅" if self.is_read else "Не прочитана❌"
        avg_rating = sum(self.rating)/len(self.rating)
        str_reviews = ''
        for review in range(len(self.reviews)):
            str_reviews += f"   {review+1}. (Rating: {self.rating[review]}) {self.reviews[review]}\n\n"

        return f"""
    Информация о книге:

        Название: {self.title}"
        Автор: {self.author}
        Год выпуска: {self.year}
        Количество страниц: {self.pages}
        Жанр: {self.genre}"
        Статус: {status}
        Средний рейтинг: {avg_rating}
        
        Отзывы:
            {str_reviews}
        """
        