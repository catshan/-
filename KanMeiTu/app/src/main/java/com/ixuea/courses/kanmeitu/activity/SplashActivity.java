package com.ixuea.courses.kanmeitu.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.WindowManager;

import com.ixuea.courses.kanmeitu.MainActivity;
import com.ixuea.courses.kanmeitu.R;
import com.ixuea.courses.kanmeitu.util.SharedPreferencesUtil;

/**
 * 启动页面
 *
 * 3秒钟后进入登录界面
 *
 * 启动界面根据苹果开发者文档可以理解为是用来让用户加快启动的
 * 而不是在上面显示你的广告和商标的（Android开发我们暂时没有找到相关的定义）
 */
public class SplashActivity extends BaseActivity {
    private Handler handler=new Handler(){
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            next();
        }
    };

    private void next() {

        Intent intent =null;
        if (sp.isLogin()) {
            //已经登录，跳转到首页
            intent = new Intent(this, MainActivity.class);
        } else {
            //否则跳转到登录界面
            intent = new Intent(this, LoginActivity.class);
        }

        //真实项目中，可能还有引导界面
        //大家可以学习我们的《Android开发项目实战之我的云音乐》课程
        //http://www.ixuea.com/courses/10
        startActivity(intent);

        //关闭当前界面
        finish();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_splash);

        //去除状态栏
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);


        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                //3秒钟后调用，这里

                //这里调用是在子线程，不能直接操作UI，需要用handler切换到主线程
                //用多个线程的目的解决，如果有耗时任务，那么就会卡界面
                //而用了多线程后，将耗时任务放到子线程，这样主线程(UI线程)就不会卡主
                handler.sendEmptyMessage(0);
            }
        },3000);
    }
}
