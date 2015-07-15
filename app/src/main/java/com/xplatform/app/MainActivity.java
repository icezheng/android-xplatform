package com.xplatform.app;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.widget.EditText;
import android.widget.Toast;
import butterknife.Bind;
import butterknife.ButterKnife;
import butterknife.OnClick;
import com.xplatform.R;
import com.xplatform.lib.IUserProfileService;
import com.xplatform.lib.IUserProfileServiceListener;
import com.xplatform.lib.KeyValueStore;
import com.xplatform.lib.UserProfile;

/**
 * Created by zsiegel on 7/14/15.
 */
public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("xplatform-lib");
    }

    private KeyValueStore keyValueStore;
    private IUserProfileService userProfileService;
    private IUserProfileServiceListener serviceListener = new IUserProfileServiceListener() {
        @Override
        public void userProfileUpdated(UserProfile userProfile) {
            Toast.makeText(
                    MainActivity.this,
                    "User profile updated : " + userProfile.getFirstName() + " " + userProfile.getLastName(),
                    Toast.LENGTH_SHORT).show();
        }

        @Override
        public void userProfileRemoved() {
            Toast.makeText(
                    MainActivity.this,
                    "User profile removed",
                    Toast.LENGTH_SHORT).show();
        }
    };

    @Bind(R.id.first_name)
    EditText firstName;

    @Bind(R.id.last_name)
    EditText lastName;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main_activity);

        ButterKnife.bind(this);

        keyValueStore = new KeyValueStore(getSharedPreferences("xplatform", MODE_PRIVATE));

        userProfileService = IUserProfileService.createUserProfileService(keyValueStore);
        userProfileService.addListener(serviceListener);
    }

    @OnClick(R.id.show)
    void show() {
        UserProfile profile = userProfileService.getUserProfile();
        if (profile == null) {
            Toast.makeText(this, "No profile stored", Toast.LENGTH_SHORT).show();
        } else {
            Toast.makeText(
                    MainActivity.this,
                    "Current profile : " + profile.getFirstName() + " " + profile.getLastName(),
                    Toast.LENGTH_SHORT).show();
        }
    }

    @OnClick(R.id.save)
    void save() {
        userProfileService.updateUserProfile(
                new UserProfile(
                        firstName.getText().toString(),
                        lastName.getText().toString()));
    }

    @OnClick(R.id.delete)
    void delete() {
        userProfileService.removeUserProfile();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        userProfileService.removeListener(serviceListener);
    }
}
