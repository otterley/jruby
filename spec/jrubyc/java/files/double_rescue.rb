class DoubleRescue
  def _call
    # no-op
  rescue LoadError => e
    e || 1 # doesn't matter
  rescue => e
    e || 2 # doesn't matter
  end

  nil.to_x rescue nil

  def self.re_raise
    begin
      load 'MISSING FILE.TMP'
    rescue LoadError => e
      raise e
    end
  rescue ScriptError
    return $!
  end
end
