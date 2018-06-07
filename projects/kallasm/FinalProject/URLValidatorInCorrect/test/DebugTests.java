public class DebugTests {
    public static void main(String[] argv){
        UrlValidator validator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
        validator.isValid("http:/home.html?name=MickeyMouse#description");
    }
}
