package android.net;

import java.net.URI;
import java.net.URISyntaxException;
import java.net.URLDecoder;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public final class Uri {
    private final String value;

    private Uri(String value) {
        this.value = value == null ? "" : value;
    }

    public static Uri parse(String value) {
        return new Uri(value);
    }

    public static Uri fromParts(
            String scheme, String part, String fragment) {
        StringBuilder result = new StringBuilder();
        if (scheme != null) result.append(scheme).append(':');
        result.append(encode(part, ""));
        if (fragment != null) {
            result.append('#').append(encode(fragment, ""));
        }
        return new Uri(result.toString());
    }

    public static Uri withAppendedPath(Uri base, String path) {
        if (base == null) throw new NullPointerException("base");
        String root = base.toString();
        if (!root.endsWith("/")) root += "/";
        return parse(root + encode(path, ""));
    }

    public String getScheme() {
        try {
            return toJavaUri().getScheme();
        } catch (Exception e) {
            return null;
        }
    }

    public String getAuthority() {
        try {
            return toJavaUri().getRawAuthority();
        } catch (Exception e) {
            return null;
        }
    }

    public String getHost() {
        try {
            return toJavaUri().getHost();
        } catch (Exception e) {
            return null;
        }
    }

    public int getPort() {
        try {
            return toJavaUri().getPort();
        } catch (Exception e) {
            return -1;
        }
    }

    public String getPath() {
        try {
            return toJavaUri().getPath();
        } catch (Exception e) {
            return null;
        }
    }

    public String getEncodedPath() {
        try {
            return toJavaUri().getRawPath();
        } catch (Exception e) {
            return null;
        }
    }

    public String getQuery() {
        try {
            return toJavaUri().getQuery();
        } catch (Exception e) {
            return null;
        }
    }

    public String getFragment() {
        try {
            return toJavaUri().getFragment();
        } catch (Exception e) {
            return null;
        }
    }

    public String getLastPathSegment() {
        List<String> segments = getPathSegments();
        return segments.isEmpty()
                ? null : segments.get(segments.size() - 1);
    }

    public List<String> getPathSegments() {
        String path = getPath();
        if (path == null || path.isEmpty()) {
            return Collections.emptyList();
        }

        List<String> result = new ArrayList<>();
        for (String segment : path.split("/")) {
            if (!segment.isEmpty()) result.add(segment);
        }
        return Collections.unmodifiableList(result);
    }

    public String getQueryParameter(String key) {
        if (key == null) return null;
        String query = getQuery();
        if (query == null) return null;

        for (String item : query.split("&")) {
            int separator = item.indexOf('=');
            String name = separator < 0
                    ? item : item.substring(0, separator);
            if (decode(name).equals(key)) {
                return separator < 0
                        ? "" : decode(item.substring(separator + 1));
            }
        }
        return null;
    }

    public boolean isHierarchical() {
        return value.indexOf(':') < 0
                || value.indexOf('/') > value.indexOf(':');
    }

    public boolean isAbsolute() {
        return getScheme() != null;
    }

    public boolean isRelative() {
        return !isAbsolute();
    }

    public Builder buildUpon() {
        return new Builder(value);
    }

    private URI toJavaUri() throws URISyntaxException {
        return new URI(value);
    }

    public static String encode(String input) {
        return encode(input, null);
    }

    public static String encode(String input, String allow) {
        if (input == null) return null;
        String encoded = URLEncoder.encode(
                input, StandardCharsets.UTF_8);
        encoded = encoded.replace("+", "%20");
        if (allow != null) {
            for (int i = 0; i < allow.length(); i++) {
                char c = allow.charAt(i);
                String code = String.format("%%%02X", (int) c);
                encoded = encoded.replace(code,
                        String.valueOf(c));
            }
        }
        return encoded;
    }

    public static String decode(String input) {
        if (input == null) return null;
        return URLDecoder.decode(
                input.replace("+", "%2B"),
                StandardCharsets.UTF_8);
    }

    @Override
    public String toString() {
        return value;
    }

    @Override
    public boolean equals(Object object) {
        return object instanceof Uri
                && value.equals(((Uri) object).value);
    }

    @Override
    public int hashCode() {
        return value.hashCode();
    }

    public static final class Builder {
        private String scheme;
        private String authority;
        private String path;
        private String query;
        private String fragment;

        public Builder() {}

        Builder(String source) {
            try {
                URI uri = new URI(source);
                scheme = uri.getScheme();
                authority = uri.getRawAuthority();
                path = uri.getRawPath();
                query = uri.getRawQuery();
                fragment = uri.getRawFragment();
            } catch (Exception ignored) {
                path = source;
            }
        }

        public Builder scheme(String value) {
            scheme = value;
            return this;
        }

        public Builder authority(String value) {
            authority = value;
            return this;
        }

        public Builder appendPath(String value) {
            if (value == null) return this;
            if (path == null || path.isEmpty()) path = "";
            if (!path.endsWith("/")) path += "/";
            path += encode(value, "");
            return this;
        }

        public Builder appendQueryParameter(
                String key, String value) {
            String item = encode(key, "") + "="
                    + encode(value, "");
            query = query == null || query.isEmpty()
                    ? item : query + "&" + item;
            return this;
        }

        public Builder encodedQuery(String value) {
            query = value;
            return this;
        }

        public Builder fragment(String value) {
            fragment = value;
            return this;
        }

        public Uri build() {
            StringBuilder result = new StringBuilder();
            if (scheme != null) result.append(scheme).append(':');
            if (authority != null) {
                result.append("//").append(authority);
            }
            if (path != null) result.append(path);
            if (query != null) result.append('?').append(query);
            if (fragment != null) {
                result.append('#').append(fragment);
            }
            return Uri.parse(result.toString());
        }
    }
}
