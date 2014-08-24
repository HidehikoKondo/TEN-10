package jp.nagohiyo.number_ten;

import jp.nagohiyo.number_ten.R;

import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

import jp.maru.mrd.IconLoader;
import jp.maru.mrd.IconCell;

public class NativeCodeAst {
    private static final int AST_ICON_WIDTH = 80;
    private static final int AST_ICON_COUNT = 4;
    private static final int DEVICE_BASE_WIDTH = 320;

    // __TEST__の部分にはメディア識別コードを入れてください
    private static final String _MEDIA_CODE = "ast01235ypzxm21q4ta8";

    private static IconLoader<Integer> _iconLoader;
    private static RelativeLayout _adMain;
    
    private NativeCodeAst() {}

    public static void initAstJni()
    {
        final number_ten activity = number_ten.getActivity();
        // UIスレッド上で、iconLoaderのメソッドを実行するためこう記述しています
        activity.runOnUiThread(new Runnable(){
            @Override
            public void run()
            {
                if (_iconLoader != null) {
                    // 最初の一回しか呼んではいけない
                    return;
                }
                NativeCodeAst.initAstJni_main(activity);
            }
        });
    }

    public static void showAstJni()
    {
        final number_ten activity = number_ten.getActivity();
        activity.runOnUiThread(new Runnable(){
            @Override
            public void run()
            {
                if(_iconLoader == null) {
                    Log.d("AST_DEBUG", "*** NativeCodeAst is not initialized!");
                    return ;
                }
                _iconLoader.startLoading();
                _adMain.setVisibility(View.VISIBLE);
            }
        });
    }

    public static void hideAstJni()
    {
        final number_ten activity = number_ten.getActivity();
        activity.runOnUiThread(new Runnable(){
            @Override
            public void run()
            {
                if(_iconLoader == null) {
                    Log.d("AST_DEBUG", "*** NativeCodeAst is not initialized!");
                    return ;
                }
                _iconLoader.stopLoading();
                _adMain.setVisibility(View.INVISIBLE);
            }
        });
    }

    /*
     * IconLoader を準備し、表示位置など初期化するメソッド
     */
    private static void initAstJni_main(number_ten activity)
    {
        _adMain = new  RelativeLayout(activity);
        LinearLayout iconAdView = new LinearLayout(activity);

        DisplayMetrics metrics = activity.getResources().getDisplayMetrics();
        RelativeLayout.LayoutParams layoutParams;
        final int FILL_PARENT = LinearLayout.LayoutParams.FILL_PARENT;

        layoutParams = new RelativeLayout.LayoutParams(FILL_PARENT, (int)(AST_ICON_WIDTH * metrics.density));


        // 画面の下部にアイコン広告を配置
        layoutParams.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
        iconAdView.setGravity(Gravity.CENTER_HORIZONTAL);
        iconAdView.setLayoutParams(layoutParams);

        // IconLoaderクラスのインスタンスを生成。
        IconLoader<Integer> iconLoader = new IconLoader<Integer>(_MEDIA_CODE, activity);
        iconLoader.setRefreshInterval(15);

        for (int i=0; i<AST_ICON_COUNT; i++) {
            final LinearLayout iconAdSubView = new LinearLayout(activity);
            LinearLayout.LayoutParams layoutSubParams =
                    new LinearLayout.LayoutParams(1, (int)(AST_ICON_WIDTH * metrics.density), 1.0f);

            int width = metrics.widthPixels;
            int icon_width = (int)(DEVICE_BASE_WIDTH * metrics.density + 0.5f);
            if(width - icon_width > 0) {
                int iconMargin = (int)((width - icon_width) / (AST_ICON_COUNT * 2));
                layoutSubParams.setMargins(iconMargin, 0, iconMargin, 0);
            }
            iconAdSubView.setLayoutParams(layoutSubParams);

            // 後述のレイアウトxmlファイル、icon.xmlからIconCellのviewを生成します。
            View view = activity.getLayoutInflater().inflate(R.layout.icon, null);

            if (view instanceof IconCell) {
                // IconLoader にIconCellのインスタンスを登録しておきます。
                ((IconCell)view).addToIconLoader(iconLoader);

                // アイコンのタイトル文字色を白色に指定。intの色指定値で任意の色に設定できます。
                ((IconCell)view).setTitleColor(0xffffffff);

                // レイアウト用の変数iconAdViewのもう一つ内側に配置するレイアウトiconAdSubViewに、
                // 生成したIconCellのインスタンスを配置しています。
                iconAdSubView.addView(view);
            }
            iconAdView.addView(iconAdSubView);
        }
                
        _adMain.addView(iconAdView);
                
        View contentView = ((ViewGroup)activity.findViewById(android.R.id.content)).getChildAt(0);
        ((ViewGroup)contentView).addView(_adMain);
        _adMain.setVisibility(View.INVISIBLE);
                
        // IconLoaderのインスタンスを参照できるように、このクラスのインスタンスを保持しておきます。
         _iconLoader = iconLoader;
    }

}