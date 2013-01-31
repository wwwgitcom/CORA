require 'net/http'


def auto_decode_dmp()
  dmp_dir = "c:\\soradump"
  system "del c:\\soradump\\*.*"

  t = Time.now

  system "mkdir auto_decode_results"

  output_dir = "auto_decode_results\\#{t.year}_#{t.mon}_#{t.day}__#{t.hour}_#{t.min}_#{t.sec}"

  system "mkdir #{output_dir}"

  puts output_dir

  while 1 do
    system "dir c:\\soradump\\"
    system "dut dump"

    dmpname = ''
    Dir.foreach(dmp_dir){ |fname|
      if (File.extname(fname) == '.dmp')
        dmpname = fname[0...-6]
        break
      end
    }
    
    if dmpname != ''
      system "Cora.exe FileName1=#{dmpname}_0.dmp FileName2=#{dmpname}_1.dmp > #{output_dir}\\#{dmpname}.txt"
    end

  end
end

#system "..\\release\\cora.exe"
auto_decode_dmp()

