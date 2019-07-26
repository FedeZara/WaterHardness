extern Adafruit_ILI9341 tft;
extern URTouch ts;

class Page {
    friend class NavigationController;
    protected:
        bool isVisible = false;

        int numButtons;
        Button* buttons;

        int numLabels;
        Label* labels;

        virtual void Setup(){

        }

        virtual void Loop(){
            if (ts.dataAvailable())
            {
                int x, y;
                ts.read();
                x = ts.getX();
                y = ts.getY();
                for(int i=0; i<numButtons; i++){
                    if(buttons[i].CheckIfClicked(x, y))
                        ExecuteButton(i);
                }
            }
        }

        virtual void ExecuteButton(int index){}

    public:     
        int BackgroundColor = 0xFFFF;
        
        void SetNumButtons(int numButtons){
            this->numButtons = numButtons;
            buttons = new Button[numButtons];
        }

        void SetNumLabels(int numLabels){
            this->numLabels = numLabels;
            labels = new Label[numLabels]; 
        }

        void AddButton(Button b, int index){
            buttons[index] = b;
        }

        void AddLabel(Label l, int index){
            labels[index] = l;
        }

        void Show(){
            isVisible = true;
            tft.fillScreen(BackgroundColor);

            Setup();

            for(int i=0; i<numLabels; i++){
                labels[i].Show();
            }
        
            for(int i=0; i<numButtons; i++){
                buttons[i].Show();
            }
        }

        void Hide(){
            isVisible = false;
        }
};