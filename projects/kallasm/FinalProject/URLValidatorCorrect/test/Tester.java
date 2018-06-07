public class Tester {
    private UrlValidator validator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
    private PartitionTester tester = new PartitionTester();
    private AutoTester autoTester = new AutoTester();

    public void testSchemePartition(){
        TestPair next;
        next = tester.getNextSchemePartition();
        int failures = 0;
        while(next != null){
            boolean result = validator.isValid(next.toString());
            if (result != next.isValid()){
                System.out.println("Fail on URL: " + next.toString());
                System.out.println("\tisValid: " + result + ". Expected: " + next.isValid());
                failures++;
            }
            next = tester.getNextSchemePartition();
        }
        if (failures > 0){
            System.out.println("Finished test of Scheme Partitions with " + failures + " failures.");
        }
        else{
            System.out.println("Passed Test of Scheme Partitions!");
        }
    }

    public void testAuthorityPartition(){
        TestPair next;
        next = tester.getNextAuthorityPartition();
        int failures = 0;
        while(next != null){
            boolean result = validator.isValid(next.toString());
            if (result != next.isValid()){
                System.out.println("Fail on URL: " + next.toString());
                System.out.println("\tisValid: " + result + ". Expected: " + next.isValid());
                failures++;
            }
            next = tester.getNextAuthorityPartition();
        }
        if (failures > 0){
            System.out.println("Finished test of Authority Partitions with " + failures + " failures.");
        }
        else{
            System.out.println("Passed Test of Authority Partitions!");
        }
    }

    public void testPathPartition(){
        TestPair next;
        next = tester.getNextPathPartition();
        int failures = 0;
        while(next != null){
            boolean result = validator.isValid(next.toString());
            if (result != next.isValid()){
                System.out.println("Fail on URL: " + next.toString());
                System.out.println("\tisValid: " + result + ". Expected: " + next.isValid());
                failures++;
            }
            next = tester.getNextPathPartition();
        }
        if (failures > 0){
            System.out.println("Finished test of Path Partitions with " + failures + " failures.");
        }
        else{
            System.out.println("Passed Test of Path Partitions!");
        }
    }

    public void testQueryPartition(){
        TestPair next;
        next = tester.getNextQueryPartition();
        int failures = 0;
        while(next != null){
            boolean result = validator.isValid(next.toString());
            if (result != next.isValid()){
                System.out.println("Fail on URL: " + next.toString());
                System.out.println("\tisValid: " + result + ". Expected: " + next.isValid());
                failures++;
            }
            next = tester.getNextQueryPartition();
        }
        if (failures > 0){
            System.out.println("Finished test of Query Partitions with " + failures + " failures.");
        }
        else{
            System.out.println("Passed Test of Query Partitions!");
        }
    }

    public void testFragmentPartition(){
        TestPair next;
        next = tester.getNextFragmentPartition();
        int failures = 0;;
        while(next != null){
            boolean result = validator.isValid(next.toString());
            if (result != next.isValid()){
                System.out.println("Fail on URL: " + next.toString());
                System.out.println("\tisValid: " + result + ". Expected: " + next.isValid());
                failures++;
            }
            next = tester.getNextFragmentPartition();
        }
        if (failures > 0){
            System.out.println("Finished test of Fragment Partitions with " + failures + " failures.");
        }
        else{
            System.out.println("Passed Test of Fragment Partitions!");
        }
    }
    public void testIsValid()
    {
        TestPair next;
        next = autoTester.getNextTestPair();
        int failures = 0;;
        while(next != null){
            boolean result = validator.isValid(next.toString());
            if (result != next.isValid()){
                System.out.println("Fail on URL: " + next.toString());
                System.out.println("\tisValid: " + result + ". Expected: " + next.isValid());
                failures++;
            }
            next = autoTester.getNextTestPair();
        }
        if (failures > 0){
            System.out.println("Finished automatic test with " + failures + " failures.");
        }
        else{
            System.out.println("Passed automatic test!");
        }
    }

    public static void main(String[] argv){
        Tester partTester = new Tester();
        System.out.println("\n############### BEGIN PARTITION TEST ###############");
        partTester.testSchemePartition();
        partTester.testAuthorityPartition();
        partTester.testPathPartition();
        partTester.testQueryPartition();
        partTester.testFragmentPartition();
        System.out.println("############### END PARTITION TEST ###############");

        System.out.println("\n############### BEGIN AUTOMATIC TEST ###############");
        partTester.testIsValid();
        System.out.println("############### END AUTOMATIC TEST ###############");
    }
}
