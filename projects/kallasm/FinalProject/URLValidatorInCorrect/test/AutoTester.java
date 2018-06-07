public class AutoTester {
    //indices: scheme, authority, path, query, fragment
    private int[] indices = {0, 0, 0, 0, 0};
    private int[] lengths = {0, 0, 0, 0, 0};
    private boolean complete = false;

    private boolean incrementIndices(){
        boolean carry = true;
        int index = 0;
        while(carry){
           indices[index]++;
           if (indices[index] >= lengths[index]){
               indices[index] = 0;
               carry = true;
               index++;
           }
           else carry = false;
           if (index >= lengths.length) return false;
        }
        return true;
    }

    private TestPair makePair(){
        String url = schemes[indices[0]].toString() + authority[indices[1]].toString() + path[indices[2]].toString() + query[indices[3]].toString() + fragment[indices[4]].toString();
        boolean valid = (schemes[indices[0]].isValid() && authority[indices[1]].isValid() && path[indices[2]].isValid() && query[indices[3]].isValid() && fragment[indices[4]].isValid());
        TestPair newPair = new TestPair(url, valid);
        return newPair;
    }

    public TestPair getNextTestPair(){
        if (complete) return null;
        TestPair nextPair = makePair();
        if (!incrementIndices()) complete = true;
        return nextPair;
    }

    AutoTester(){
        setLengths();
    }

    public void setLengths(){
        lengths[0] = schemes.length;
        lengths[1] = authority.length;
        lengths[2] = path.length;
        lengths[3] = query.length;
        lengths[4] = fragment.length;
    }

    public TestPair [] schemes = {
            new TestPair("http:", true),
            new TestPair("", false),
            new TestPair("ht!tp:", false),
            new TestPair("1http:", false),
            new TestPair("http", false)
    };

    public TestPair [] authority = {
            new TestPair( "//google.com", true),
            new TestPair( "", false),
            new TestPair( "//google[.com", false),
            new TestPair( "//google.com::8000", false),
            new TestPair("/google.com", false)
    };

    public TestPair [] path = {
            new TestPair("/home.html", true),
            new TestPair("", true),
            new TestPair("/^", false),
            new TestPair("//home.html", false)
    };

    public TestPair [] query = {
            new TestPair("?name=MickeyMouse", true),
            new TestPair("", true),
            new TestPair("?name=Mickey&title=Mouse", true),
            new TestPair("[?name=MickeyMouse", false)
    };

    public TestPair [] fragment = {
            new TestPair("#description", true),
            new TestPair("", true)
    };
}
