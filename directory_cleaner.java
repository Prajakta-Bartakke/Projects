import java.lang.*;
import java.util.*;
import java.io.*;

//for checksum
import java.security.MessageDigest;
import java.io.FileInputStream;

class directory_cleaner
{
 public static void main(String arg[])throws Exception
 {
  BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
  
  System.out.println("enter directory name:");
  String dir=br.readLine();
  
  Cleaner cobj=new Cleaner(dir);
  cobj.cleandirectoryemptyfile();
  cobj.cleandirectoryduplicatefile();
 }
}

class Cleaner
{
 public File fdir=null;
 public Cleaner(String name)
 {
  fdir=new File(name);
  if(!fdir.exists())
  {
   System.out.println("Invalid directory name");
   System.exit(0);
  }
 }
 
 public void cleandirectoryemptyfile()
 {
  File filelist[]=fdir.listFiles();
  int cnt=0;
  
  for(File file:filelist)
  {
   //System.out.println(file.getName()+" "+file.length());
   
   if(file.length()==0)
   {
    System.out.println("empty file name:"+file.getName());
    file.delete();
    cnt++;
   }
  }
  System.out.println("total empty file deleted:"+cnt);
   
 }
 
 public void cleandirectoryduplicatefile()
 {
  File filelist[]=fdir.listFiles();
  int duplicate=0;
  byte bytearr[]=new byte[1024];   //bucket to read data
  //file thevnyasahich
  LinkedList<String> lobj=new LinkedList<String>();
  int rcount=0;
  try
  {
  MessageDigest digest=MessageDigest.getInstance("MD5");
  
  if(digest==null)
  {
   System.out.println("unable to get md5");
   System.exit(0);
  }
  for(File file:filelist)
  {
   FileInputStream fis=new FileInputStream(file);
   //System.out.println(file.getName()+" "+file.length());
   
   if(file.length()!=0)
   {
    while((rcount=fis.read(bytearr))!=-1)
    {
     digest.update(bytearr,0,rcount);   //0 offset pasun
    }
   }
   
   byte bytes[]=digest.digest();    //to get hash byte
   
   StringBuilder sb=new StringBuilder();
   
   for(int i=0;i<bytes.length;i++)   
   {
    sb.append(Integer.toString((bytes[i] & 0xff)+0x100,16).substring(1));
   }
   System.out.println("file:"+file.getName()+"checksum:"+sb);
   //add checkum in linked list
   if(lobj.contains(sb.toString()))   
   {
    if(!file.delete())
    {
     System.out.println("unable to delete"+file.getName());
    }
    else
    {
     System.out.println("file deleted:"+file.getName());
     duplicate++;
    }
   }
   else
   {
    lobj.add(sb.toString());
   }
   
   fis.close();
  }
  System.out.println("total dupliacte file deleted:"+duplicate);
   
 }
 
 catch(Exception obj)
 {
  System.out.println("exception occured");
 }
 finally
 {
 
 }
 
}
}