$h = 1

def write_time( line )
	if ($h == 1)
		time = Time.now - 60
		$h = 0
	else
		time = Time.now
		$h = 1
	end
	line[19] = (time.hour.to_i + '0'.ord).chr
	line[20] = (time.min.to_i + '0'.ord).chr
	line[21] = (time.sec.to_i + '0'.ord).chr
	nsec1 = (time.nsec / 100000000) % 10
	nsec2 = (time.nsec / 10000000) % 10
	nsec3 = (time.nsec / 1000000) % 10
	line[22] = ('0'.ord + nsec1).chr
	line[23] = ('0'.ord + nsec2).chr
	line[24] = ('0'.ord + nsec3).chr
end

def write_index( line, index )
	line[9] = ((index / 100000000) % 10 + '0'.ord).chr
	line[10] = ((index / 10000000) % 10 + '0'.ord).chr
	line[11] = ((index / 1000000) % 10 + '0'.ord).chr
	line[12] = ((index / 100000) % 10 + '0'.ord).chr
	line[13] = ((index / 10000) % 10 + '0'.ord).chr
	line[14] = ((index / 1000) % 10 + '0'.ord).chr
	line[15] = ((index / 100) % 10 + '0'.ord).chr
	line[16] = ((index / 10) % 10 + '0'.ord).chr
	line[17] = ((index / 1) % 10 + '0'.ord).chr
end
