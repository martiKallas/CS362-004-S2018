

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {
   private UrlValidator validator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
   private PartitionTester partitionTester = new PartitionTester();
   private AutoTester autoTester = new AutoTester();


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
   }

   public void testSchemePartition(){
      TestPair next;
      next = partitionTester.getNextSchemePartition();
      int failures = 0;
      while(next != null){
         boolean result = validator.isValid(next.toString());
         if (result != next.isValid()){
            System.out.println("Fail on URL: " + next.toString());
            System.out.println("\tisValid: " + result + ". Expected: " + next.isValid());
            failures++;
         }
         next = partitionTester.getNextSchemePartition();
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
      next = partitionTester.getNextAuthorityPartition();
      int failures = 0;
      while(next != null){
         boolean result = validator.isValid(next.toString());
         if (result != next.isValid()){
            System.out.println("Fail on URL: " + next.toString());
            System.out.println("\tisValid: " + result + ". Expected: " + next.isValid());
            failures++;
         }
         next = partitionTester.getNextAuthorityPartition();
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
      next = partitionTester.getNextPathPartition();
      int failures = 0;
      while(next != null){
         boolean result = validator.isValid(next.toString());
         if (result != next.isValid()){
            System.out.println("Fail on URL: " + next.toString());
            System.out.println("\tisValid: " + result + ". Expected: " + next.isValid());
            failures++;
         }
         next = partitionTester.getNextPathPartition();
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
      next = partitionTester.getNextQueryPartition();
      int failures = 0;
      while(next != null){
         boolean result = validator.isValid(next.toString());
         if (result != next.isValid()){
            System.out.println("Fail on URL: " + next.toString());
            System.out.println("\tisValid: " + result + ". Expected: " + next.isValid());
            failures++;
         }
         next = partitionTester.getNextQueryPartition();
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
      next = partitionTester.getNextFragmentPartition();
      int failures = 0;;
      while(next != null){
         boolean result = validator.isValid(next.toString());
         if (result != next.isValid()){
            System.out.println("Fail on URL: " + next.toString());
            System.out.println("\tisValid: " + result + ". Expected: " + next.isValid());
            failures++;
         }
         next = partitionTester.getNextFragmentPartition();
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
           try {
               boolean result = validator.isValid(next.toString());
               if (result != next.isValid()) {
                   System.out.println("Fail on URL: " + next.toString());
                   System.out.println("\tisValid: " + result + ". Expected: " + next.isValid());
                   failures++;
               }
           }
           catch(ExceptionInInitializerError e){
               System.out.println("Fail on URL: " + next.toString());
               System.out.println("\tExceptionInInitializerError should not occur");
               failures++;
           }
           catch(NoClassDefFoundError f){
               System.out.println("Fail on URL: " + next.toString());
               System.out.println("\tNoClassDefFoundError exception should not occur");
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
      UrlValidatorTest urlTester = new UrlValidatorTest("Final Project Test");
      System.out.println("\n############### BEGIN PARTITION TEST ###############");
      urlTester.testSchemePartition();
      urlTester.testAuthorityPartition();
      urlTester.testPathPartition();
      urlTester.testQueryPartition();
      urlTester.testFragmentPartition();
      System.out.println("############### END PARTITION TEST ###############");


      System.out.println("\n############### BEGIN AUTOMATIC TEST ###############");
      urlTester.testIsValid();
      System.out.println("############### END AUTOMATIC TEST ###############");
   }

}
