package com.xplatform.lib;

import android.content.SharedPreferences;

/**
 * Created by zsiegel on 7/14/15.
 */
public class KeyValueStore extends IKeyValueStorage {

    private final SharedPreferences sharedPreferences;

    public KeyValueStore(SharedPreferences sharedPreferences) {
        this.sharedPreferences = sharedPreferences;
    }

    @Override
    public void writeString(String key, String value) {
        sharedPreferences.edit().putString(key, value).apply();
    }

    @Override
    public void writeInt32(String key, int value) {
        sharedPreferences.edit().putInt(key, value).apply();
    }

    @Override
    public void writeBool(String key, boolean value) {
        sharedPreferences.edit().putBoolean(key, value).apply();
    }

    @Override
    public void writeBinary(String key, byte[] value) {
        throw new RuntimeException("Unable to store binary data");
    }

    @Override
    public void remove(String key) {
        sharedPreferences.edit().remove(key).apply();
    }

    @Override
    public String readString(String key) {
        return sharedPreferences.getString(key, null);
    }

    @Override
    public Integer readInt32(String key) {
        int value = sharedPreferences.getInt(key, -1);
        return (value == -1) ? null : value;
    }

    @Override
    public boolean readBool(String key) {
        return sharedPreferences.getBoolean(key, false);
    }

    @Override
    public byte[] readBinary(String key) {
        throw new RuntimeException("Unable to get binary data");
    }

}
