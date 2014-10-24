/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.KaNot;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;
import android.view.KeyEvent;
import android.view.MotionEvent;
import java.io.File;

import android.content.res.AssetManager;

public class KaNotActivity extends Activity {

    KaNotView mView;
    AssetManager assetManager;
    
    static 
	{
         System.loadLibrary("KaNot");
	}
    
    @Override
    public boolean onTouchEvent(MotionEvent event) {

        // get pointer index from the event object
        int pointerIndex = event.getActionIndex();

        // get pointer ID
        int pointerId = event.getPointerId(pointerIndex);

        // get masked (not specific to a pointer) action
        int maskedAction = event.getActionMasked();

        switch (maskedAction) {

        case MotionEvent.ACTION_DOWN:
        case MotionEvent.ACTION_POINTER_DOWN: {
        	KaNotLib.inputEvent(1,(int)event.getX(pointerIndex),(int)event.getY(pointerIndex),pointerId);
          break;
        }
        case MotionEvent.ACTION_MOVE: { // a pointer was moved
          // TODO use data
          break;
        }
        case MotionEvent.ACTION_UP:
        case MotionEvent.ACTION_POINTER_UP:
        case MotionEvent.ACTION_CANCEL: {
          // TODO use data
          break;
        }
        }
        

        return true;
    } 
	
	public native void killswitch();
	
	public void kill()
	{
		//finish();
		Log.w("LOL","Reached java ok!");
	}
	
	public void onDestroy() 
	{
        super.onDestroy();
        android.os.Process.killProcess(android.os.Process.myPid());
    }  
	
    @Override protected void onCreate(Bundle icicle) {
    	assetManager = getAssets();
    	KaNotLib.GetManager(assetManager);
        super.onCreate(icicle);
        mView = new KaNotView(getApplication());
	setContentView(mView);
    }

    @Override protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override protected void onResume() {
        super.onResume();
        mView.onResume();
    }
}
