package android.content.pm;

public final class ManifestMerger {
    public ManifestDocument merge(
            ManifestDocument base, ManifestDocument overlay) {
        if (base == null || base.root == null) {
            throw new IllegalArgumentException("Base manifest is missing");
        }

        if (overlay == null || overlay.root == null) {
            throw new IllegalArgumentException("Overlay manifest is missing");
        }

        if (!base.root.name.equals(overlay.root.name)) {
            throw new IllegalArgumentException("Manifest roots differ");
        }

        ManifestNode merged = base.root.deepCopy();
        mergeNode(merged, overlay.root);

        ManifestDocument result = new ManifestDocument(merged);
        result.revision = base.revision + 1;
        result.parsed = true;
        return result;
    }

    private void mergeNode(ManifestNode target, ManifestNode source) {
        for (int i = 0; i < source.attributeCount; i++) {
            target.setAttribute(
                    source.attributeNames[i],
                    source.attributeValues[i]);
        }

        for (int i = 0; i < source.childCount; i++) {
            ManifestNode incoming = source.children[i];
            ManifestNode existing = findMatching(target, incoming);

            if (existing == null) {
                target.addChild(incoming.deepCopy());
            } else {
                mergeNode(existing, incoming);
            }
        }

        if (source.text != null && source.text.length() > 0) {
            target.text = source.text;
        }
    }

    private ManifestNode findMatching(
            ManifestNode parent, ManifestNode incoming) {
        String incomingName = incoming.getAttribute("android:name");

        for (int i = 0; i < parent.childCount; i++) {
            ManifestNode candidate = parent.children[i];

            if (!candidate.name.equals(incoming.name)) continue;

            String candidateName = candidate.getAttribute("android:name");

            if (incomingName == null && candidateName == null) {
                return candidate;
            }

            if (incomingName != null && incomingName.equals(candidateName)) {
                return candidate;
            }
        }

        return null;
    }
}
