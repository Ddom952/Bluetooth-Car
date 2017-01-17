package com.example.dominikbaljon.steering_test;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.text.TextPaint;
import android.util.AttributeSet;
import android.view.View;
import android.widget.SeekBar;

/**
 * TODO: document your custom view class.
 */
public class CustomSeekBar extends SeekBar {

    private Rect rect;
    private Paint paint ;
    private int seekbar_height;

    public CustomSeekBar(Context context) {
        super(context);

    }

    public CustomSeekBar(Context context, AttributeSet attrs) {

        super(context, attrs);
        rect = new Rect();
        paint = new Paint();
        seekbar_height = 8;
    }

    public CustomSeekBar(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
    }

    @Override
    protected synchronized void onDraw(Canvas canvas) {

        rect.set(0 + getThumbOffset() + 2,
                (getHeight() / 2) - (seekbar_height/2),
                getWidth() - getThumbOffset() - 2,
                (getHeight() / 2) + (seekbar_height/2));

        paint.setColor(Color.GRAY);

        canvas.drawRect(rect, paint);

        if (this.getProgress() > 60) {


            rect.set(getWidth() / 2,
                    (getHeight() / 2) - (seekbar_height/2),
                    getWidth() / 2 + (getWidth() / 120) * (getProgress() - 60),
                    getHeight() / 2 + (seekbar_height/2));

            paint.setColor(Color.CYAN);
            canvas.drawRect(rect, paint);

        }

        if (this.getProgress() < 60) {

            rect.set(getWidth() / 2 - ((getWidth() / 120) * (60 - getProgress())),
                    (getHeight() / 2) - (seekbar_height/2),
                    getWidth() / 2,
                    getHeight() / 2 + (seekbar_height/2));

            paint.setColor(Color.CYAN);
            canvas.drawRect(rect, paint);

        }

        super.onDraw(canvas);
    }
}
