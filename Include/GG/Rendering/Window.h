namespace gg
{
    class CWindow
    {
    public:

        bool IsOpen() { return _open; }

        void Create( unsigned w, unsigned h, const char* t );
        void Clear();
        void PollEvents();
        void Present();

    private:
        void* _backendWinPtr;
        void* _backendRendererPtr;
        bool _open = true;
    };
}