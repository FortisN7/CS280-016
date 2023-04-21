class Novel : public Story {
    public:
        Novel(std::string type = "Novel", int numWords = 0) : Story(type), numWords(numWords) {}

        int getWords() const { 
            return numWords; 
        }
        void setWords(int newNumWords) { 
            numWords = newNumWords; 
        }

        int getLowerLimit() const { 
            return lowerLimit;
        }

        int getPages() const override {
            return pages;
        }
        void setPages(int numWordsPerPage) override {
            pages = numWords / numWordsPerPage;
            if (pages < lowerLimit) {
                int deficit = lowerLimit - pages;
                msg = "Pages must be added to the book to satisfy the requirements of a " + type + ": " + to_string(deficit);
            } else {
                msg = "Book is accepted.";
            }
        }

    private:
        int numWords;
        const int lowerLimit = 101;
};