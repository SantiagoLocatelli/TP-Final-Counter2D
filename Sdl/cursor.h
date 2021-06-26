#ifndef __CURSOR_H__
#define __CURSOR_H__

class Cursor {
    private:
        // int x;
        // int y;
        double degrees;
        int screen_w;
        int screen_h;

    public:

        Cursor(int screen_w, int screen_h);
        void setAt(double degrees);
        double getDegrees();
        void lookAt(int x, int y, int relX, int relY);
};

#endif