package android.location;

import java.io.IOException;
import java.util.List;
import java.util.Locale;

public class Geocoder {
    public Geocoder(Object context, Locale locale) {}

    public List<Object> getFromLocation(
            double latitude, double longitude, int maxResults)
            throws IOException {
        throw new RuntimeException("Stub!");
    }

    public List<Object> getFromLocationName(
            String locationName, int maxResults)
            throws IOException {
        throw new RuntimeException("Stub!");
    }
}
