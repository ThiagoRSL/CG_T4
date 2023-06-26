#ifndef MOUSEMANAGER_H
#define MOUSEMANAGER_H


class MouseManager
{
    public:
        static MouseManager &shared_instance() {static MouseManager mouseManager; return mouseManager;}
        MouseManager();
        int PosX;
        int PosY;
    protected:

    private:
};

#endif // MOUSEMANAGER_H
