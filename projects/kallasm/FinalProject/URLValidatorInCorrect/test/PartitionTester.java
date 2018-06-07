public class PartitionTester {
    private int schemeIndex = 0;
    private int authorityIndex = 0;
    private int pathIndex = 0;
    private int queryIndex = 0;
    private int fragmentIndex = 0;
    public TestPair [] schemes = {
            new TestPair("http:", true),
            new TestPair("", false),
            new TestPair("ht!tp:", false),
            new TestPair("1http:", false),
            new TestPair("http", false)
    };

    public TestPair [] authority = {
            new TestPair( "//google.com", true),
            new TestPair( "", true),
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
            new TestPair("?name=Mickey+Mouse", false),
            new TestPair("?&", false)
    };

    public TestPair [] fragment = {
            new TestPair("#description", true),
            new TestPair("", true),
            new TestPair("{}", false)
    };

    public TestPair getNextSchemePartition(){
        if (schemeIndex == schemes.length){
            schemeIndex = 0;
            return null;
        }
        String url = schemes[schemeIndex].toString() + authority[0].toString() + path[0].toString() + query[0].toString() + fragment[0].toString();
        boolean valid = (schemes[schemeIndex].isValid() && authority[0].isValid() && path[0].isValid() && query[0].isValid() && fragment[0].isValid());
        schemeIndex++;
        return new TestPair(url, valid);
    }

    public TestPair getNextAuthorityPartition(){
        if (authorityIndex == authority.length){
            authorityIndex = 0;
            return null;
        }
        String url = schemes[0].toString() + authority[authorityIndex].toString() + path[0].toString() + query[0].toString() + fragment[0].toString();
        boolean valid = (schemes[0].isValid() && authority[authorityIndex].isValid() && path[0].isValid() && query[0].isValid() && fragment[0].isValid());
        authorityIndex++;
        return new TestPair(url, valid);
    }

    public TestPair getNextPathPartition(){
        if (pathIndex == path.length){
            pathIndex = 0;
            return null;
        }
        String url = schemes[0].toString() + authority[0].toString() + path[pathIndex].toString() + query[0].toString() + fragment[0].toString();
        boolean valid = (schemes[0].isValid() && authority[0].isValid() && path[pathIndex].isValid() && query[0].isValid() && fragment[0].isValid());
        pathIndex++;
        return new TestPair(url, valid);
    }

    public TestPair getNextQueryPartition(){
        if (queryIndex == query.length){
            queryIndex = 0;
            return null;
        }
        String url = schemes[0].toString() + authority[0].toString() + path[0].toString() + query[queryIndex].toString() + fragment[0].toString();
        boolean valid = (schemes[0].isValid() && authority[0].isValid() && path[0].isValid() && query[queryIndex].isValid() && fragment[0].isValid());
        queryIndex++;
        return new TestPair(url, valid);
    }

    public TestPair getNextFragmentPartition(){
        if (fragmentIndex == fragment.length){
            fragmentIndex = 0;
            return null;
        }
        String url = schemes[0].toString() + authority[0].toString() + path[0].toString() + query[0].toString() + fragment[fragmentIndex].toString();
        boolean valid = (schemes[0].isValid() && authority[0].isValid() && path[0].isValid() && query[0].isValid() && fragment[fragmentIndex].isValid());
        fragmentIndex++;
        return new TestPair(url, valid);
    }

}
