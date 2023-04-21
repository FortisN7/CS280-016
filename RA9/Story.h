#include <string>

using namespace std;

class Story {
    protected:
        string title;
        string author;
        int pages = 0;
        string type;
        string msg;

    public:
        Story(string type) : type(type) {}
        virtual ~Story() {}

        string getTitle() const {
            return title;
        }
        void setTitle(string newTitle) {
            title = newTitle;
        }

        string getAuthor() const {
            return author;
        }
        void setAuthor(string newAuthor) {
            author = newAuthor;
        }

        virtual int getPages() const = 0;
        virtual void setPages(int numWordsPerPage) = 0;
        
        string getType() const {
            return type;
        }
        void setType(string newType) {
            type = newType;
        }

        string getMsg() const {
            return msg;
        }
        void setMsg(string newMsg) {
            msg = newMsg;
        }
};