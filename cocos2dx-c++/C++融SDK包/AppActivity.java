/****************************************************************************
Copyright (c) 2015-2017 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import com.tystore.onlinepay.TyPay;
import com.ty.ctr.ex.PayParams;
import com.ty.ctr.ex.PayResultInterface;
import com.ty.ctr.ex.BaseResponse;

import org.cocos2dx.lib.Cocos2dxActivity;

/****************************************************************************
 Copyright (c) 2015-2017 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

import android.widget.Toast;

public class AppActivity extends Cocos2dxActivity {

    private static AppActivity s_instance = null;
    public static AppActivity getInstance() { return s_instance; }

    private String apSecert = "D5B2BDF5BE2B4B5B976FC83F9630528C";//ap密钥
    private String appId = "201079853";	//应用ID
    private String chargeId = "FB29C56635794668A5479BF3D268FFE5";//计费代码 、计费点
    private String  apName = "福建资讯通信息科技有限公司";//公司名称
    private String  appName = "经典天天跑酷";//APP名称
    private String  chargeName = "800金币";//道具名称
    private int  price = 800;//价格 单位分 1￥=100分
    private int  priceType = 1;//计费类型 1-按次计费；2-包月计费，此计费类型和chargeId类型一致
    private String  exdata = "";
    private String  orderId = "1234";//AP自定义订单号，服务器透传对应txid字段
    private String channelId = "1234" + System.currentTimeMillis() / 10;//AP自定义渠道号，服务器透传
    private String csPhoneNum = "";//AP客服电话


    Context context;
    PayParams mPayParams;
    TyPay mTyPay;
    BaseResponse baseResponse = new BaseResponse();


    /*
            * 按次计费测试产品参数
            */
    private String ciAppId = "1076644";
    private String ciChargeid = "265D4902E8CB4BCCE0530100007F6303";
    private String ciapSecert = "25FB4F3FE6822411E0530100007F66DE";

    /*
     * 包月计费测试产品参数
     */
    private String byAppid = "1075942";
    private String byChargeid = "32DD2CE9677269D9E0530100007F39DB";
    private String byapSecertd = "1FD9B6FAF17E3E54E0530100007FA781";

    //回调接口实例
    private PayResultInterface mPayCallback = new PayResultInterface(){
        @Override
        public void execute(BaseResponse arg0) {
            // TODO Auto-generated method stub
            JniMethods.getPayResult(arg0.getResult());
            Log.e("main", arg0.getPayType() + " "+ arg0.getResult() + " " + arg0.getMsg() + " " +arg0.getOrdersn());
            sendHander(handler ,arg0.getPayType() + " "+ arg0.getResult() + " " + arg0.getMsg() + " " +arg0.getOrdersn(),0);

        }
    };


    private long mkeyTime = 0;
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        //二次返回退出
        if (keyCode == KeyEvent.KEYCODE_BACK) {
            if ((System.currentTimeMillis() - mkeyTime) > 2000) {
                mkeyTime = System.currentTimeMillis();
                Log.i("time",String.valueOf(mkeyTime / 10));
                Toast.makeText(this, "请再按一次退出游戏", Toast.LENGTH_LONG).show();
            } else {
                finish();
                System.exit(0);
            }
            return false;
        }
        return super.onKeyDown(keyCode, event);
    }

    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);

        //初始化支付类
        mTyPay = TyPay.getInstance();
        //设置参数
        mPayParams = new PayParams();
        mPayParams.setApName(apName);
        mPayParams.setAppid(appId);
        mPayParams.setAppName(appName);
        mPayParams.setChannelId(channelId);
        mPayParams.setCsPhone(csPhoneNum);
        mPayParams.setPayInterface(mPayCallback);

        this.context = this;
        s_instance = this;


    }


    public Handler handler = new Handler()
    {
        @Override
        public void handleMessage(Message msg)
        {
            if (!Thread.currentThread().isInterrupted())
            {
                switch (msg.what)
                {
                    case 0:
                        Toast.makeText(context, (String)msg.obj, Toast.LENGTH_LONG).show();
                        break;
                    case 1:
                        //支付方法
                        mTyPay.init(context, mPayParams);
                        mTyPay.pay(chargeId,orderId, chargeName, price, priceType, exdata);
//                        Toast.makeText(context,"哈哈，扣你钱！",Toast.LENGTH_SHORT).show();
                        Log.i("cocos 订单号：", chargeName);
                        break;
                    case 2:
                        //包月退订方法
                        mTyPay.init(context,mPayParams);
                        mTyPay.quitPay(chargeId, orderId);
                        break;

                    default:
                        break;
                }
            }
        }
    } ;
    public void sendHander(Handler h,String sData,int flag){
        Message toMain = new Message();
        if (null != sData){
            toMain.obj = sData;
        }
        toMain.what = flag;
        h.sendMessage(toMain);
    }

    public void setParam(String schargeId,String schargeName,int sprice)
    {
        chargeId = schargeId;
        chargeName = schargeName;
        price = sprice;
        Log.i("cocos  activity",chargeId+" "+chargeName+ " "+price);
    }

    public int getBaseResponse()
    {
        Log.i("cocos  activity result:",String.valueOf(baseResponse.getResult()));
        return baseResponse.getResult();
    }

}

