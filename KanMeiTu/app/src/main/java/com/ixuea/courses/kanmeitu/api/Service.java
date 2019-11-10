package com.ixuea.courses.kanmeitu.api;

import com.ixuea.courses.kanmeitu.domain.Image;
import com.ixuea.courses.kanmeitu.domain.response.ListResponse;

import io.reactivex.Observable;
import retrofit2.http.GET;

/**
 * Created by smile on 02/03/2019.
 */
public interface Service {
    /**
     * 获取图片列表
     * @return
     */
    @GET("v1/images")
    Observable<ListResponse<Image>> images();
}
