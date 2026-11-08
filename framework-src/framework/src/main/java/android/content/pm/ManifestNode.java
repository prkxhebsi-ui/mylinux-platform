package android.content.pm;

public final class ManifestNode {
    public String name;
    public String text = "";
    public String[] attributeNames = new String[8];
    public String[] attributeValues = new String[8];
    public ManifestNode[] children = new ManifestNode[8];
    public ManifestNode parent;
    public int attributeCount;
    public int childCount;

    public ManifestNode(String name) {
        if (name == null || name.length() == 0) {
            throw new IllegalArgumentException("Empty XML element name");
        }
        this.name = name;
    }

    public void setAttribute(String key, String value) {
        if (key == null || value == null) return;

        for (int i = 0; i < attributeCount; i++) {
            if (attributeNames[i].equals(key)) {
                attributeValues[i] = value;
                return;
            }
        }

        if (attributeCount == attributeNames.length) {
            String[] names = new String[attributeCount * 2];
            String[] values = new String[attributeCount * 2];

            for (int i = 0; i < attributeCount; i++) {
                names[i] = attributeNames[i];
                values[i] = attributeValues[i];
            }

            attributeNames = names;
            attributeValues = values;
        }

        attributeNames[attributeCount] = key;
        attributeValues[attributeCount] = value;
        attributeCount++;
    }

    public String getAttribute(String key) {
        for (int i = 0; i < attributeCount; i++) {
            if (attributeNames[i].equals(key)) {
                return attributeValues[i];
            }
        }
        return null;
    }

    public boolean hasAttribute(String key) {
        return getAttribute(key) != null;
    }

    public void removeAttribute(String key) {
        for (int i = 0; i < attributeCount; i++) {
            if (attributeNames[i].equals(key)) {
                for (int j = i; j < attributeCount - 1; j++) {
                    attributeNames[j] = attributeNames[j + 1];
                    attributeValues[j] = attributeValues[j + 1];
                }
                attributeCount--;
                return;
            }
        }
    }

    public void addChild(ManifestNode child) {
        if (child == null) return;

        if (child.parent != null) {
            throw new IllegalArgumentException("Node already has a parent");
        }

        if (childCount == children.length) {
            ManifestNode[] expanded = new ManifestNode[childCount * 2];

            for (int i = 0; i < childCount; i++) {
                expanded[i] = children[i];
            }

            children = expanded;
        }

        child.parent = this;
        children[childCount++] = child;
    }

    public ManifestNode getChild(String tag) {
        for (int i = 0; i < childCount; i++) {
            if (children[i].name.equals(tag)) {
                return children[i];
            }
        }
        return null;
    }

    public ManifestNode[] getChildren(String tag) {
        int count = 0;

        for (int i = 0; i < childCount; i++) {
            if (tag == null || children[i].name.equals(tag)) count++;
        }

        ManifestNode[] result = new ManifestNode[count];
        int position = 0;

        for (int i = 0; i < childCount; i++) {
            if (tag == null || children[i].name.equals(tag)) {
                result[position++] = children[i];
            }
        }

        return result;
    }

    public void appendText(String value) {
        if (value != null) text += value;
    }

    public ManifestNode deepCopy() {
        ManifestNode copy = new ManifestNode(name);
        copy.text = text;

        for (int i = 0; i < attributeCount; i++) {
            copy.setAttribute(attributeNames[i], attributeValues[i]);
        }

        for (int i = 0; i < childCount; i++) {
            copy.addChild(children[i].deepCopy());
        }

        return copy;
    }
}
