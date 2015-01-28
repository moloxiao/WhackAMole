package org.cocos2dx.cpp;

import android.app.Activity;
import android.util.Log;

import com.tallbigup.android.gds.nativenotify.NotifyManager;

public class NativeNotifyService {
	
	private static Activity activity;
	
	public static void init(Activity activity){
		NativeNotifyService.activity = activity;
	}
	
	public static void startNativeNotify(){
		Log.i("MCH",">>>>>startNativeNotify");
		NotifyManager.setNextNotification(activity, 
				1000*60, "打地鼠", "快来消灭老鼠，拯救地球粮食啦");
	}
}
