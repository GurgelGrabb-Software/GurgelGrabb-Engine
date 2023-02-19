namespace gg
{
    class CWindow
    {
    public:
        void Create( unsigned w, unsigned h, const char* t );
        void Clear();
        void Present();

    private:
        void* _backendWinPtr;
        void* _backendRendererPtr;
    };
}