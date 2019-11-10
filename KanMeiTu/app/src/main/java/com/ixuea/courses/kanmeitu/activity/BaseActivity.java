package com.ixuea.courses.kanmeitu.activity;

import android.os.Bundle;

import com.ixuea.courses.kanmeitu.util.SharedPreferencesUtil;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class BaseActivity extends AppCompatActivity {

    /**
     * 访问修饰符改为protected
     */
    protected SharedPreferencesUtil sp;

    /**
     * 重写了setContentView方法
     * 因为在子类调用了setContentView设置布局
     * @param layoutResID
     */
    @Override
    public void setContentView(int layoutResID) {
        super.setContentView(layoutResID);

        //配置文件
        sp = SharedPreferencesUtil.getInstance(getApplicationContext());

        //其他的公共逻辑也可以这样重构
        //详细的大家可以学习我们的《Android开发项目实战之我的云音乐》课程
        //http://www.ixuea.com/courses/10
    }
}
