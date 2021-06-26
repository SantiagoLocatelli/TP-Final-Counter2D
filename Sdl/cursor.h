#ifndef __CURSOR_H__
#define __CURSOR_H__

class Cursor {
    private:
        int x;
        int y;
        double degrees;

    public:

        Cursor();
        void setAt(int x, int y, double degrees);
        double getDegrees();
        void lookAt(int x, int y, int relX, int relY);
};

#endif