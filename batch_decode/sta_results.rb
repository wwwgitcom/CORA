








def sta_per(fname, rate_head)
  snr  = 0
  rate = 0
  dok  = 0


  hdmp = File.open(fname, "r")

  hdmp.each_line{|lstr|
    if (lstr =~ /LSTF, SNR (\d+.\d+) dB/)
      snr = $1
    elsif (lstr =~ /ht-sig ok: sig=.*, mcs=(\d+), length=(\d+) Bytes/)
      rate = $1
    elsif (lstr =~ /frame decode done (\d)/)
      dok = $1

      rate_head[rate.to_i][snr.to_i][dok.to_i] += 1

      #puts "#{snr}\t#{rate}\t#{dok} \t #{rate_head[rate.to_i][snr.to_i][dok.to_i]}"
    end
  }

  hdmp.close
end



def sta_txt_in_dir(dir, arr)
  new_dir = dir + "\\"
  begin
    Dir.foreach(new_dir){ |sub_dir|
      _dir = new_dir + sub_dir
      _dir = _dir.downcase

      if (File.directory?(_dir) && sub_dir != "." && sub_dir != "..")
        #puts _dir
        puts "staging subdir #{_dir}"
        sta_txt_in_dir(_dir, arr)
      elsif (File.extname(_dir) == ".txt")
        #puts "staging #{_dir}"
        sta_per(_dir, arr)
      end
    }
  rescue Exception=>e
    	puts e
	end
end


def report_per(arr)
  puts "=== PER v.s. SNR ==="
  puts "rate \t snr \t pos_cnt\t neg_cnt \t ratio"
  for rate in (8...15)
    for snr in (1...50)
      pos_cnt = arr[rate][snr][1]
      neg_cnt = arr[rate][snr][0]

      puts "#{rate}\t#{snr}\t#{pos_cnt}\t#{neg_cnt}\t#{neg_cnt.to_f / (pos_cnt + neg_cnt + 1).to_f}"
      
    end
  end
end


def sta_per_in_dir(dir)
  # mcs 8 - 15
  rate_head = Array.new(15){ |snrindex|
    Array.new(50){|cntindex|
      Array.new(2, 0)
    }
  }

  sta_txt_in_dir(dir, rate_head)

  report_per(rate_head)
end


if ARGV.count == 1
  sta_per_in_dir(ARGV[0])
end
