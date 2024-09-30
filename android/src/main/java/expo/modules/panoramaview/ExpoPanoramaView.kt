package expo.modules.panoramaview

import android.annotation.SuppressLint
import android.app.Activity
import android.content.Context
import android.os.Bundle
import android.os.Handler
import android.os.Message
import android.view.SurfaceHolder
import android.view.SurfaceView
import android.view.ViewGroup
import android.view.Window
import android.view.WindowManager
import android.widget.SeekBar
import expo.modules.core.interfaces.Package
import expo.modules.core.interfaces.ReactActivityLifecycleListener
import expo.modules.kotlin.AppContext
import expo.modules.kotlin.viewevent.EventDispatcher
import expo.modules.kotlin.views.ExpoView

fun formatDuration(duration: Long): String {
    val totalSeconds: Int = (duration / 1000).toInt()
    val totalMinutes = totalSeconds / 60
    val seconds: Int = totalSeconds % 60
    val minutes: Int = totalMinutes % 60
    val hours: Int = totalMinutes / 60

    var result = "${if (hours == 0) "" else String.format("%02d:", hours)}${
        String.format(
            "%02d",
            minutes
        )
    }:${String.format("%02d", seconds)}"

    return result
}


class ExpoPanoramaView(context: Context, appContext: AppContext) : ExpoView(context, appContext) {

    private val onProgress by EventDispatcher()
    private val onPlayStateChanged by EventDispatcher()
    private val onLog by EventDispatcher()

//    constructor() : this() {
//        onLog(mapOf("message" to "view initialized"))
//    }

    private var surfaceViewCallback: SurfaceHolder.Callback = object : SurfaceHolder.Callback {

        override fun surfaceCreated(holder: SurfaceHolder) {
            pInit()
            nSetSurface(holder.surface)
            nOpenFile(filePath!!)
            onLog(mapOf("message" to "surface created"))
        }

        override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
            nSetSize(width, height)
            onLog(mapOf("message" to "surface changed"))
        }

        override fun surfaceDestroyed(holder: SurfaceHolder) {
//            nReleaseSurface()
        }

    }

    internal var surfaceView: SurfaceView = SurfaceView(context).also {

        val holder = it.holder
        holder.addCallback(surfaceViewCallback)

        val layoutParams = ViewGroup.LayoutParams(1920, 1080)
        layoutParams.width = ViewGroup.LayoutParams.MATCH_PARENT
        layoutParams.height = ViewGroup.LayoutParams.MATCH_PARENT
        it.layoutParams = layoutParams

        addView(it)
    }

    private var handler: Handler = Handler {
        when (it.what) {
            PROGRESS_UPDATE -> {
                if (isSeeking) {
                    return@Handler true
                }
                val ms: Long = it.obj as Long
                onProgress(mapOf("position" to ms))
            }

            PLAY_STATE_UPDATE -> {
                when (it.arg1) {
                    PLAY_STATE_START -> {
//                        Timber.d("PLAY_STATE_START")
                        isPlaying = true
                        onPlayStateChanged(mapOf("state" to "playing"))
                    }

                    PLAY_STATE_PAUSE -> {
//                        Timber.d("PLAY_STATE_PAUSE")
                        isPlaying = false
                        onPlayStateChanged(mapOf("state" to "paused"))
                    }

                    PLAY_STATE_COMPLETE -> {
//                        Timber.d("PLAY_STATE_COMPLETE")
                        isPlaying = false
                        nSeek(0)
                        onPlayStateChanged(mapOf("state" to "completed"))
                    }

                    PLAY_STATE_SEEK_START -> {
//                        Timber.d("PLAY_STATE_SEEK_START")
                    }

                    PLAY_STATE_SEEK_COMPLETE -> {
//                        Timber.d("PLAY_STATE_SEEK_COMPLETE")
                        isSeeking = false
                    }
                }
            }

        }
        return@Handler true
    }

    private val playListener = object : PlayListener {
        override fun onProgressChanged(positionMS: Long) {
            handler.sendMessage(Message().apply {
                what = PROGRESS_UPDATE
                obj = positionMS
            })
        }

        override fun onPlayStateChanged(playState: Int) {
            handler.sendMessage(Message().apply {
                what = PLAY_STATE_UPDATE
                arg1 = playState
            })
        }
    }

    private val lifecycleListener: ReactActivityLifecycleListener = object : ReactActivityLifecycleListener {

        override fun onCreate(activity: Activity?, savedInstanceState: Bundle?) {
            super.onCreate(activity, savedInstanceState)
//            requestWindowFeature(Window.FEATURE_NO_TITLE)
//
//            window.setFlags(
//                WindowManager.LayoutParams.FLAG_FULLSCREEN,
//                WindowManager.LayoutParams.FLAG_FULLSCREEN
//            )
//            window.addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON)
//            setContentView(R.layout.activity_play)
//            filePath = intent.getStringExtra("path")
//
            pInit()
            onLog(mapOf("message" to "player initialized"))

//            btn_play.text = "播放"
//            addSurfaceView()
//
//            initViews()
        }

        override fun onResume(activity: Activity?) {
            super.onResume(activity)
            nSetPlayStateListener(playListener)
        }

        override fun onPause(activity: Activity?) {
            super.onPause(activity)
            nRemovePlayStateListener()
        }

        override fun onDestroy(activity: Activity?) {
            nStop()
            nDestroy()
            super.onDestroy(activity)
        }
    }

//    override fun createReactActivityLifecycleListeners(activityContext: Context?): List<ReactActivityLifecycleListener> {
//        return listOf(lifecycleListener)
//    }

    private var filePath: String? = null

    private var isPlaying = false

    private var isSeeking = false



    external fun pInit(): Unit
    external fun nDestroy()
    external fun nStart()
    external fun nStop()
    external fun nOpenFile(filePath: String): Boolean
    external fun nSetSurface(surfaceView: Any)
    external fun nSetSize(width: Int, height: Int)
    external fun nSeek(position: Long)
    external fun nGetDuration(): Long
    external fun nSetPlayStateListener(listener: Any)
    external fun nRemovePlayStateListener()
    external fun nIsPlaying(): Boolean

    companion object {
        private val TAG = "PlayActivity"
        const val PROGRESS_UPDATE: Int = 1
        const val PLAY_STATE_UPDATE: Int = 2

        init {
            System.loadLibrary("panorama-player")
        }
    }
}
