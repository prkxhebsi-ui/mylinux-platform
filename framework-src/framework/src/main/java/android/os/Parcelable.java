package android.os;

public interface Parcelable {
    int CONTENTS_FILE_DESCRIPTOR = 1;
    int PARCELABLE_WRITE_RETURN_VALUE = 1;

    void writeToParcel(Parcel destination, int flags);

    int describeContents();

    interface Creator<T> {
        T createFromParcel(Parcel source);
        T[] newArray(int size);
    }
}
