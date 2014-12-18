
#ifndef NativeCodeAst_h
#define NativeCodeAst_h

namespace AstExt {
    class NativeCodeAst {
    public:
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        // 広告表示開始用と、停止用、そして初期化用の3つのメソッドを定義
        static void initAst();
        static void showAst();
        static void hideAst();
#endif
        
    };
}

#endif