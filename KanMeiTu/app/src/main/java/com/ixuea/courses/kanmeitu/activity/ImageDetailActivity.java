package com.ixuea.courses.kanmeitu.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;

import com.github.chrisbanes.photoview.PhotoView;
import com.ixuea.courses.kanmeitu.R;
import com.ixuea.courses.kanmeitu.util.Constants;
import com.ixuea.courses.kanmeitu.util.ImageUtil;

public class ImageDetailActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_image_detail);

        PhotoView pv = findViewById(R.id.pv);

        //获取传递过来的参数
        String uri = getIntent().getStringExtra(Constants.ID);

        //显示图片
        ImageUtil.show(this,pv,uri);
    }
}
