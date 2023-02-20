namespace gg
{
    class CWindow
    {
    public:
        bool IsOpen() const;

        void Create( unsigned w, unsigned h, const char* t );
        void Destroy();
        void Clear();
        void PollEvents();
        void Present();

    private:
        void* _backendWinPtr;
        void *_backendRendererPtr;
        bool _open = true;
    };
}