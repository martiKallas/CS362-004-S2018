public class TestPair {
    private String component;
    private boolean validity;

    TestPair(String value, boolean isValid){
        component = value;
        validity = isValid;
    }

    @Override
    public String toString(){
        return component;
    }

    public boolean isValid(){
        return validity;
    }

}
