class PageController {
    private:
        Page** pages;
        int numPages;
        Adafruit_ILI9341 *tft;
        URTouch *ts;
        int currPage = -1;
    public:
        PageController() {
            SetNumPages(0);
        } 

        void SetTft(Adafruit_ILI9341 *tft){
            this->tft = tft;
            for(int i=0; i<numPages; i++){
                if(pages[i] != nullptr)
                    pages[i]->SetTft(tft);
            }
        }

        void SetTs(URTouch *ts){
            this->ts = ts;
            for(int i=0; i<numPages; i++){
                if(pages[i] != nullptr)
                    pages[i]->SetTs(ts);
            }
        }

        void SetNumPages(int numPages){
            this->numPages = numPages;
            pages = new Page*[numPages];
        }

        void AddPage(Page* p, int index){
            pages[index] = p;
            pages[index]->SetTft(tft);
            pages[index]->SetTs(ts);
        }

        void NavigateTo(int index){
            if(index == currPage)
                return;
            currPage = index;
            pages[currPage]->Show();
        }

        void OnLoop(){
            pages[currPage]->OnLoop();
        }
};