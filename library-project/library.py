from book import Book

class Library:
    def __init__(self):
        self.books = []
        self.next_id = 1

    def add_book(self, title, author, year, pages, genre):
        book = Book(self.next_id, title, author, year, pages, genre)
        self.books.append(book)
        self.next_id += 1

    def remove_book_by_id(self, book_id):
        self.books = [book for book in self.books if book.id != book_id]

    def find_by_title(self, title):
        result = []
        for book in self.books:
            if title.lower() in book.title.lower():
                result.append(book)
        return result
    
    def find_by_author(self, author):
        result = []
        for book in self.books:
            if author.lower() in book.author.lower():
                result.append(book)
        return result
    
    def find_by_genre(self, genre):
        result = []
        for book in self.books:
            if genre.lower() in book.genre.lower():
                result.append(book)
        return result
    
    def get_unread_books(self):
        result = []
        for book in self.books:
            if not book.is_read:
                result.append(book)
        return result
    
    def get_statistics(self):
        if not self.books:
            return "Библиотека пуста‼️"
        amount_read = 0
        avg_rating_list = []
        genres = dict()
        for book in self.books:
            if book.rating:
                avg_rating_list.append(sum(book.rating)/len(book.rating))
            if book.genre in genres:
                genres[book.genre] += 1
            else:
                genres[book.genre] = 1
            if book.is_read:
                amount_read += 1

        avg_rating = "Н/Д" if not avg_rating_list else sum(avg_rating_list)/len(avg_rating_list)

        max_genre_amount = 0
        max_genre_name = []
        for genre in genres:
            if max_genre_amount < genres[genre]:
                max_genre_name = [genre]
                max_genre_amount = genres[genre]
            elif max_genre_amount == genres[genre]:
                max_genre_name.append(genre)
        str_max_genre = ''
        for genre in max_genre_name:
            str_max_genre += genre + ", "

        return f"""
        📊Статистика:

        Всего книг: {len(self.books)}
        Книг прочитано: {amount_read}
        Книг не прочитано: {len(self.books)-amount_read}
        Средний рейтинг: {avg_rating}
        Самый популярный жанр(ы): {str_max_genre}

        """
    
    def display_all_books(self):
        title_length = len("Название")
        author_length = len("Автор")
        genre_length = len("Жанр")
        for book in self.books:
            if title_length < len(book.title):
                title_length = len(book.title)
            if author_length < len(book.author):
                author_length = len(book.author)
            if genre_length < len(book.genre):
                genre_length = len(book.genre)
        title_length += 3
        author_length += 3
        genre_length += 3
        str_res = f"Название{" "*(title_length-len("Название"))}Автор{" "*(author_length-len("Автор"))}Жанр{" "*(genre_length-len("Жанр"))}Год\n"
        for book in self.books:
            str_res += f"{book.title+" "*(title_length-len(book.title))}{book.author+" "*(author_length-len(book.author))}{book.genre+" "*(genre_length-len(book.genre))}{book.year}\n"
        return str_res

