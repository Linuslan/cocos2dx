package org.cocos2dx.cpp;


import android.util.Log;

public class JniMethods {

	// begin set blurry enable or disable (native)
//	private native static void nativeSetGameParamsFromOnline(String strBlurry); //0 or 1
//	public static void SetGameParamsFromOnline()
//	{
//		String strBlurry = AppActivity.getBlurry();
//		nativeSetGameParamsFromOnline(strBlurry);
//	}
	// end
	
	// begin event with label (cpp2java)
//	public static void onEvent(String eventId)
//	{
//		MobclickAgent.onEvent(AppActivity.getInstance(), eventId);
//	}
	// end

	private native static void nativeGetPayResult(int type);
	public static void getPayResult(int type)
	{
		nativeGetPayResult(type);
	}

	public static void setSdkparam(String chargeId,String chargeName,int price)
	{
//		MobclickAgent.onEvent(AppActivity.getInstance(), eventId);
		AppActivity.getInstance().setParam(chargeId,chargeName,price);
		Log.i("cocos java jniMethods",chargeId+" "+chargeName+ " "+price);
	}

//	requestPayWith1 (cpp2java)
	public static void requestPayWith1()
	{
		AppActivity.getInstance().runOnUiThread(new Runnable() {
			public void run(){
//				if (AppActivity.getIsDebug()) {
//					Log.i("bstsdk", "requestPayWith 1 JniMethods");
//				}
				AppActivity.getInstance().sendHander(AppActivity.getInstance().handler,"", 1);
			}
		});
	}
	
	//requestPayWith2 (cpp2java)
//	public static void requestPayWith2()
//	{
//		AppActivity.getInstance().runOnUiThread(new Runnable() {
//			public void run(){
////				if (AppActivity.getIsDebug()) {
//					Log.i("bstsdk", "requestPayWith 2 JniMethods");
////				}
//				AppActivity.getInstance().requestPayWith(2);
//			}
//		});
//	}
}
