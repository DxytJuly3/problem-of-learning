public class StudentClass_Test {
	public void Test1() {
		Student stu1 = new Student("20222201", "张三", "男", 21);
		Student stu2 = new Student("20222202", "李四", "男", 20);
		Student stu3 = new Student("20222203", "王五", "男", 22);
		Student stu4 = new Student("20222204", "翠花", "女", 19);
		Student stu5 = new Student("20222205", "丫丫", "女", 18);
		Student stu6 = new Student("20222206", "菲菲", "女", 20);
		System.out.println(stu1);
		System.out.println(stu2);
		System.out.println(stu3);
		System.out.println(stu4);
		System.out.println(stu5);
		System.out.println(stu6);

		System.out.println("一共有 " + Student.getStudentCount() + "个学生");
	}
	public void Test2() {
		Student [] StudentArr = new Student[10];
		
	}
	
	public static void main(String args[]) {
		
	}
}
