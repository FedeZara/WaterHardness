class NavigationController {
    private:
        Page** pages;
        int numPages;
        int currPage = -1;
    public:
        NavigationController() {
            SetNumPages(0);
        } 

        void SetNumPages(int numPages){
            this->numPages = numPages;
            pages = new Page*[numPages];
        }

        void AddPage(Page* p, int index){
            pages[index] = p;
        }

        void NavigateTo(int index){
            if(index == currPage)
                return;
            
            if(currPage != -1)
                pages[currPage]->Hide();

            currPage = index;

            pages[currPage]->Show();
        }

        void OnLoop(){
            pages[currPage]->Loop();
        }
};