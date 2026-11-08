package android.graphics.pdf;

public class PdfDocument {
    public static class PageInfo {
        public int getPageNumber() {
            throw new RuntimeException("Stub!");
        }

        public int getPageWidth() {
            throw new RuntimeException("Stub!");
        }

        public int getPageHeight() {
            throw new RuntimeException("Stub!");
        }
    }

    public static class Page {
        public PageInfo getInfo() {
            throw new RuntimeException("Stub!");
        }

        public Object getCanvas() {
            throw new RuntimeException("Stub!");
        }
    }

    public Page startPage(PageInfo info) {
        throw new RuntimeException("Stub!");
    }

    public void finishPage(Page page) {
        throw new RuntimeException("Stub!");
    }

    public void close() {
        throw new RuntimeException("Stub!");
    }
}
