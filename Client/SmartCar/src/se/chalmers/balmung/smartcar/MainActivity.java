/** Main class. This establishes a connection to the server, sends to the server
 *  and also listens to the camera feed.
 * @author Team Pegasus (simeon)
 */

package se.chalmers.balmung.smartcar;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.OptionalDataException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.Reader;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {
    private SharedPreferences settings;
	
	private Socket socket;
	private String serverPort = "0";
	private String serverIp;	
	private String prevMsg = "";
	
	ImageView videoView;
	
	TextView BumpSensorCounter;//my aDDITION
	
    private int displayWidth;
    private int displayHeight;
	private boolean videoPlaying = false;
	String data = "";
	Handler timerHandler = new Handler();
    Runnable timerRunnable = new Runnable() {

        @Override
        public void run() {
            new DownloadImageTask(videoView).execute("http://" + serverIp + "/cam_pic.php");
            videoView.getLayoutParams().width = displayWidth;
    		videoView.getLayoutParams().height = displayHeight;
            
            timerHandler.postDelayed(this, 40);
        }
    };
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		settings = getSharedPreferences("DefaultPrefs", 0);
		serverIp = settings.getString("serverIp", "10.0.2.2");
		serverPort = settings.getString("serverPort", "8787");

		new Thread(new ClientThread()).start();
		setContentView(R.layout.activity_main);
		videoView = (ImageView) findViewById(R.id.videoView);
		displayWidth = videoView.getLayoutParams().width;
		displayHeight = videoView.getLayoutParams().height;
		this.data = receive();//mine""""""""""""""
	    BumpSensorCounter= (TextView)findViewById(R.id.BumpSensorCounter);//Mine"""""??****
	    BumpSensorCounter.setText(data);//mine""""**********
    }
	
	public void updateBumpCounter() {
		BumpSensorCounter.setText(data);//mine""""**********
	}
	
	@Override
	protected void onResume() {
		super.onResume();	
		
		settings = getSharedPreferences("DefaultPrefs", 0);
		serverIp = settings.getString("serverIp", "10.0.2.2");
		serverPort = settings.getString("serverPort", "8787");
		
		new Thread(new ClientThread()).start();
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		Intent intent = new Intent(this, SettingsActivity.class);
		startActivity(intent);
		return super.onOptionsItemSelected(item);
	}
	
	public void onAction(View view) {
		String message = "";
		send(message);
	}
	
	public void onVideo(View view) {	
		videoView.setImageResource(android.R.color.transparent);
		
		if (videoPlaying == true) {
			timerHandler.removeCallbacks(timerRunnable);
			videoPlaying = false;
		} else {
			videoPlaying = true;
			new DownloadImageTask(videoView).execute("http://" + serverIp + "/cam_pic.php");
			timerHandler.postDelayed(timerRunnable, 0);					
		}
	}

	public void send(String message) {
		if (!prevMsg.contains(message)) {
			prevMsg = message;
			try {
				PrintWriter out = new PrintWriter(new BufferedWriter(
						new OutputStreamWriter(socket.getOutputStream())), true);
				out.println(message);
			} catch (UnknownHostException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
	//Mine*******************!!!!!!!!!!!!
	public String receive() {
	    StringBuilder sb = new StringBuilder();

			BufferedReader br = null;
			String str;
			
			try {
				br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			} catch (Exception e1) {
				Log.e("hello", "" + e1.getMessage());
			}
			 try {
				while ((str = br.readLine()) != null) {
				      sb.append(str);
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
			return sb.toString();
		
	}
			 
	class ClientThread implements Runnable {

		@Override
		public void run() {
			try {
				InetAddress serverAddr = InetAddress.getByName(serverIp);
				serverPort = "8787";
				socket = new Socket(serverAddr, Integer.parseInt(serverPort));
				while(true) {
					MainActivity.this.data = MainActivity.this.receive();
					MainActivity.this.updateBumpCounter();
				}
			} catch (UnknownHostException e1) {
				e1.printStackTrace();
			} catch (IOException e1) {
				e1.printStackTrace();
			}
		}
	}
	
	public void onClick(View view){
		send((String) view.getTag());
	
	}
	


				
			
	private class DownloadImageTask extends AsyncTask<String, Void, Bitmap> {
	    ImageView bmImage;

	    public DownloadImageTask(ImageView bmImage) {
	        this.bmImage = bmImage;
	    }

	    protected Bitmap doInBackground(String... urls) {
	        String urldisplay = urls[0];
	        Bitmap mIcon11 = null;
	        try {
	            InputStream in = new java.net.URL(urldisplay).openStream();
	            mIcon11 = BitmapFactory.decodeStream(in);
	        } catch (Exception e) {
	            Log.e("Error", e.getMessage());
	            e.printStackTrace();
	        }
	        return mIcon11;
	    }

	    protected void onPostExecute(Bitmap result) {
	        bmImage.setImageBitmap(result);
	    }
	}
}
