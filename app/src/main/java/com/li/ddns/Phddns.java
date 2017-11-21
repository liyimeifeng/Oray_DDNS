package com.li.ddns;

/**
 * Created by Lee on 2017/11/20 0020 11:45.
 */

public class Phddns {

    static {
        System.loadLibrary("phddns");
    }

    public native void run(String szHost, String szUserID, String szUserPWD, String nicName, String logfile);

}
