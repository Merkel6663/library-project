from book import Book

class Library:
    def __init__(self):
        self.books = []
        self.next_id = 1

    def add_book(self, book: Book):
        book.id = self.next_id
        self.next_id += 1
        self.books.append(book)

    def remove_book_by_id(self, book_id):
        for book in self.books:
            if book.id == book_id:
                self.books.remove(book)

    def find_by_title(self, title):
        result = []
        for book in self.books:
            if book.title == title:
                result.append(book.id)
        return result
    
    def find_by_author(self, author):
        result = []
        for book in self.books:
            if book.author == author:
                result.append(book.id)
        return result
    
    def find_by_genre(self, genre):
        result = []
        for book in self.books:
            if book.genre == genre:
                result.append(book.id)
        return result
    
    def get_unread_books(self):
        result = []
        for book in self.books:
            if not book.is_read:
                result.append(book.id)
        return result
    
    def get_statistics(self):
        amount_read = 0
        avg_rating = []
        genres = dict()
        for book in self.books:
            avg_rating.append(sum(book.rating)/len(book.rating))
            if book.genre in genres:
                genres[book.genre] += 1
            else:
                genres[book.genre] = 1
            if book.is_read:
                amount_read += 1

        max_genre_amount = 0
        max_genre_name = []
        for genre in genres:
            if max_genre_amount < genres[genre]:
                max_genre_name.append(genre)
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
        Средний рейтинг: {sum(avg_rating)/len(avg_rating)}
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
        str = f"Название{" "*(title_length-len("Название"))}Автор{" "*(author_length-len("Автор"))}Жанр{" "*(title_length-len("Жанр"))}Год\n"
        for book in self.books:
            str += f"{book.title+" "*(title_length-len(book.title))}{book.author+" "*(author_length-len(book.author))}{book.genre+" "*(genre_length-len(book.genre))}{book.year}"
        return str

