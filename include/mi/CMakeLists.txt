SET ( include_files Argument.hpp
      Attribute.hpp
      AttributeSet.hpp
      BooleanAttribute.hpp
      Clamp.hpp
      CommandTemplate.hpp
      DoubleNumericAttribute.hpp
      Exporter.hpp
      FileNameConverter.hpp
      Importer.hpp
      Limits.hpp
      NumericAttribute.hpp
      ParallelFor.hpp
      Parse.hpp
      PriorityQueue.hpp
      Progress.hpp
      StringAttribute.hpp
      SystemInfo.hpp
      Thread.hpp
      Timer.hpp
      Tokenizer.hpp
      TripleNumericAttribute.hpp
    )
INSTALL ( FILES ${include_files}
          DESTINATION include/mi
          PERMISSIONS OWNER_READ GROUP_READ WORLD_READ )

