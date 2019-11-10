package com.ixuea.courses.kanmeitu.util;

import android.app.Activity;
import android.widget.ImageView;

import com.bumptech.glide.Glide;
import com.bumptech.glide.request.RequestOptions;
import com.ixuea.courses.kanmeitu.R;

public class ImageUtil {
    public static void show(Activity activity, ImageView imageView, String uri) {
        RequestOptions options = getCommonRequestOptions();
        Glide.with(activity).load(uri).apply(options).into(imageView);
    }

    private static RequestOptions getCommonRequestOptions() {
        RequestOptions options = new RequestOptions();

        //加载前占位图
        options.placeholder(R.drawable.ic_place_holder);

        //加载错误图
        options.error(R.drawable.ic_place_holder);

        options.centerCrop();

        //测试，禁用所有缓存
        //options.diskCacheStrategy(DiskCacheStrategy.NONE);

        return options;
    }
}
