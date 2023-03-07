// $(document).ready(function () {
// });
window.onload = function () {
  InitChinaMap();
  InitPressure();
  InitPie();
  initWordCloud();
};

function InitPressure() {
  var myChart = echarts.init(document.getElementById("chartPressure"));
  var option = {
    tooltip: {
      formatter: "{a} <br/>{b} : {c}%",
    },
    series: [
      {
        name: "Pressure",
        type: "gauge",
        progress: {
          show: true,
        },
        detail: {
          valueAnimation: true,
          formatter: "{value}",
        },
        data: [{ value: 50, name: "SCORE" }],
      },
    ],
  };
  myChart.setOption(option);
}

function InitPie() {
  var myChart = echarts.init(document.getElementById("chartPie"));
  option = {
    title: {
      text: "Weather Statistics",
      subtext: "Fake Data",
      left: "center",
    },
    tooltip: {
      trigger: "item",
      formatter: "{a} <br/>{b} : {c} ({d}%)",
    },
    legend: {
      bottom: 10,
      left: "center",
      data: ["CityA", "CityB", "CityD", "CityC", "CityE"],
    },
    series: [
      {
        type: "pie",
        radius: "65%",
        center: ["50%", "50%"],
        selectedMode: "single",
        data: [
          { value: 1548, name: "CityE" },
          { value: 735, name: "CityC" },
          { value: 510, name: "CityD" },
          { value: 434, name: "CityB" },
          { value: 335, name: "CityA" },
        ],
        emphasis: {
          itemStyle: {
            shadowBlur: 10,
            shadowOffsetX: 0,
            shadowColor: "rgba(0, 0, 0, 0.5)",
          },
        },
      },
    ],
  };
  myChart.setOption(option);
}

function InitChinaMap() {
  // 同一个id可以一直初始化，这样2个chart界面会叠加
  var myChart = echarts.init(document.getElementById("chartChinaMap"));
  myChart.setOption({
    // 进行相关配置
    tooltip: {}, // 鼠标移到图里面的浮动提示框
    dataRange: {
      // show: false,
      min: 0,
      max: 1000,
      text: ["High", "Low"],
      realtime: true,
      calculable: true,
      color: ["#ff3333", "orange", "yellow", "lime", "aqua"],
      textStyle: {
        color: "#fff",
      },
    },

    geo: {
      name: "全国",
      map: "china", // 表示中国地图
      roam: true, // 是否开启鼠标缩放和平移漫游
      label: {
        show: true, // 是否显示对应地名
        color: "#fff",
      },

      // 普通样式。
      itemStyle: {
        borderColor: "rgba(100,149,237,1)",
        borderWidth: "0.5",
        areaColor: "#1b1b1b",
      },

      // 高亮样式。
      emphasis: {
        itemStyle: {
          areaColor: null,
          shadowOffsetX: 0,
          shadowOffsetY: 0,
          shadowBlur: 20,
          borderWidth: 0,
          shadowColor: "rgba(0, 0, 0, 0.5)",
        },
        label: {
          show: true,
          // 高亮时标签的文字。
          // formatter: "This is a emphasis label.",
        },
      },
    },
    series: [
      {
        name: "第1条serie", // 浮动框的标题
        type: "map",
        // type: "effectScatter", // 数据点的类型
        // coordinateSystem: "geo", // 对应上方配置
        geoIndex: 0,
        data: [
          { name: "吉林", value: 44 },
          { name: "湖北", value: 810 },
          { name: "四川", value: 453 },
          { name: "青海", value: 666 },
        ],
      },
      {
        name: "第2条serie",
        type: "map", // 地图如果可以选中，数据点的type就只能是map，否则可以为圆圈
        geoIndex: 0,
        data: [
          { name: "广东", value: 995 },
          { name: "湖南", value: 180 },
        ],
      },
    ],
  });
}

function initWordCloud() {
  var keywords = {
    markPoint: 18574,
    pie: 38929,
    roseType: 969,
    label: 37517,
    emphasis: 12053,
    name: 15418,
    type: 22905,
    gridIndex: 5146,
    normal: 49487,
    itemStyle: 33837,
    min: 4500,
    silent: 5744,
    animation: 4840,
    offsetCenter: 232,
    inverse: 3706,
    borderColor: 4812,
    markLine: 16578,
    line: 76970,
    radar: 15964,
    data: 60679,
    dataZoom: 24347,
    tooltip: 43420,
    toolbox: 25222,
    geo: 16904,
    parallelAxis: 4029,
    parallel: 5319,
    max: 3393,
    bar: 43066,
    heatmap: 3110,
    map: 20285,
    animationDuration: 3425,
    animationDelay: 2431,
    splitNumber: 5175,
    axisLine: 12738,
    lineStyle: 19601,
    splitLine: 7133,
    axisTick: 8831,
    axisLabel: 17516,
    pointer: 590,
    color: 23426,
    title: 38497,
    formatter: 15214,
    slider: 7236,
    legend: 66514,
    grid: 28516,
    smooth: 1295,
    smoothMonotone: 696,
    sampling: 757,
    feature: 12815,
    saveAsImage: 2616,
    polar: 6279,
    calculable: 879,
    backgroundColor: 9419,
    excludeComponents: 130,
    show: 20620,
    text: 2592,
    icon: 2782,
    dimension: 478,
    inRange: 1060,
    animationEasing: 2983,
    animationDurationUpdate: 2259,
    animationDelayUpdate: 2236,
    animationEasingUpdate: 2213,
    angleAxis: 5469,
    showTitle: 484,
    dataView: 2754,
    restore: 932,
    timeline: 10104,
    range: 477,
    value: 5732,
    precision: 878,
    target: 1433,
    zlevel: 5361,
    symbol: 8718,
    interval: 7964,
    symbolSize: 5300,
    showSymbol: 1247,
    inside: 8913,
    orient: 4205,
    boundaryGap: 5073,
    nameGap: 4896,
    zoomLock: 571,
    hoverAnimation: 2307,
    legendHoverLink: 3553,
    stack: 2907,
    throttle: 466,
    connectNulls: 897,
    clipOverflow: 826,
    startValue: 551,
    minInterval: 3292,
    opacity: 3097,
    splitArea: 4775,
    filterMode: 635,
    end: 409,
    left: 6475,
    funnel: 2238,
    lines: 6403,
    baseline: 431,
    align: 2608,
    coord: 897,
    nameTextStyle: 7477,
    width: 4338,
    shadowBlur: 4493,
    effect: 929,
    period: 225,
    areaColor: 631,
    borderWidth: 3654,
    nameLocation: 4418,
    position: 11723,
    containLabel: 1701,
    scatter: 10718,
    areaStyle: 5310,
    scale: 3859,
    pieces: 414,
    categories: 1000,
    selectedMode: 3825,
    itemSymbol: 273,
    effectScatter: 7147,
    fontStyle: 3376,
    fontSize: 3386,
    margin: 1034,
    iconStyle: 2257,
    link: 1366,
    axisPointer: 5245,
    showDelay: 896,
    graph: 22194,
    subtext: 1442,
    selected: 2881,
    barCategoryGap: 827,
    barGap: 1094,
    barWidth: 1521,
    coordinateSystem: 3622,
    barBorderRadius: 284,
    z: 4014,
    polarIndex: 1456,
    shadowOffsetX: 3046,
    shadowColor: 3771,
    shadowOffsetY: 2475,
    height: 1988,
    barMinHeight: 575,
    lang: 131,
    symbolRotate: 2752,
    symbolOffset: 2549,
    showAllSymbol: 942,
    transitionDuration: 993,
    bottom: 3724,
    fillerColor: 229,
    nameMap: 1249,
    barMaxWidth: 747,
    radius: 2103,
    center: 2425,
    magicType: 3276,
    labelPrecision: 248,
    option: 654,
    seriesIndex: 935,
    controlPosition: 121,
    itemGap: 3188,
    padding: 3481,
    shadowStyle: 347,
    boxplot: 1394,
    labelFormatter: 264,
    realtime: 631,
    dataBackgroundColor: 239,
    showDetail: 247,
    showDataShadow: 217,
    x: 684,
    valueDim: 499,
    onZero: 931,
    right: 3255,
    clockwise: 1035,
    itemWidth: 1732,
    trigger: 3840,
    selectedOffset: 670,
    startAngle: 1293,
    minAngle: 590,
    top: 4637,
    avoidLabelOverlap: 870,
    labelLine: 3785,
    sankey: 2933,
    endAngle: 213,
    start: 779,
    roam: 1738,
    fontWeight: 2828,
    fontFamily: 2490,
    subtextStyle: 2066,
    indicator: 853,
    sublink: 708,
    zoom: 1038,
    subtarget: 659,
    length: 1060,
    itemSize: 505,
    controlStyle: 452,
    edgeLabel: 1188,
    radiusAxisIndex: 354,
    scaleLimit: 1313,
    geoIndex: 535,
    regions: 1892,
    itemHeight: 1290,
    nodes: 644,
    candlestick: 3166,
    crossStyle: 466,
    edges: 369,
    links: 3277,
    layout: 846,
    barBorderColor: 721,
    barBorderWidth: 498,
    treemap: 3865,
    y: 367,
    valueIndex: 704,
    showLegendSymbol: 482,
    mapValueCalculation: 492,
    optionToContent: 264,
    handleColor: 187,
    handleSize: 271,
    showContent: 1853,
    angleAxisIndex: 406,
    endValue: 327,
    triggerOn: 1720,
    contentToOption: 169,
    buttonColor: 71,
    rotate: 1144,
    hoverLink: 335,
    outOfRange: 491,
    textareaColor: 58,
    textareaBorderColor: 58,
    textColor: 60,
    buttonTextColor: 66,
    category: 336,
    hideDelay: 786,
    alwaysShowContent: 1267,
    extraCssText: 901,
    effectType: 277,
    force: 1820,
    rippleEffect: 723,
    edgeSymbolSize: 329,
    showEffectOn: 271,
    gravity: 199,
    edgeLength: 193,
    layoutAnimation: 152,
    length2: 169,
    enterable: 957,
    dim: 83,
    readOnly: 143,
    levels: 444,
    textGap: 256,
    pixelRatio: 84,
    nodeScaleRatio: 232,
    draggable: 249,
    brushType: 158,
    radarIndex: 152,
    large: 182,
    edgeSymbol: 675,
    largeThreshold: 132,
    leafDepth: 73,
    childrenVisibleMin: 73,
    minSize: 35,
    maxSize: 35,
    sort: 90,
    funnelAlign: 61,
    source: 336,
    nodeClick: 200,
    curveness: 350,
    areaSelectStyle: 104,
    parallelIndex: 52,
    initLayout: 359,
    trailLength: 116,
    boxWidth: 20,
    back: 53,
    rewind: 110,
    zoomToNodeRatio: 80,
    squareRatio: 60,
    parallelAxisDefault: 358,
    checkpointStyle: 440,
    nodeWidth: 49,
    color0: 62,
    layoutIterations: 56,
    nodeGap: 54,
    repulsion: 276,
    tiled: 105,
    currentIndex: 145,
    axisType: 227,
    loop: 97,
    playInterval: 112,
    borderColor0: 23,
    gap: 43,
    autoPlay: 123,
    showPlayBtn: 25,
    breadcrumb: 119,
    colorMappingBy: 85,
    id: 18,
    blurSize: 85,
    minOpacity: 50,
    maxOpacity: 54,
    prevIcon: 12,
    children: 21,
    shape: 98,
    nextIcon: 12,
    showNextBtn: 17,
    stopIcon: 21,
    visibleMin: 83,
    visualDimension: 97,
    colorSaturation: 56,
    colorAlpha: 66,
    emptyItemWidth: 10,
    inactiveOpacity: 4,
    activeOpacity: 4,
    showPrevBtn: 19,
    playIcon: 26,
    ellipsis: 19,
    gapWidth: 19,
    borderColorSaturation: 10,
    handleIcon: 2,
    handleStyle: 6,
    borderType: 1,
    constantSpeed: 1,
    polyline: 2,
    blendMode: 1,
    dataBackground: 1,
    textAlign: 1,
    textBaseline: 1,
    brush: 3,
  };

  var data = [];
  for (var name in keywords) {
    data.push({
      name: name,
      value: Math.sqrt(keywords[name]),
    });
  }

  var dataAppend = [
    { name: "Alberl教程", value: 300 },
    { name: "bilnkUI", value: 299 },
  ];

  data.push(...dataAppend);

  var chart = echarts.init(document.getElementById("chartWordCloud"));
  var maskImage = new Image();
  maskImage.src = "./assets/chartMask.png";
  var option = {
    tooltip: {},
    series: [
      {
        type: "wordCloud",
        gridSize: 2,
        sizeRange: [12, 50],
        rotationRange: [-90, 90],
        // shape: "pentagon",
        // width: 530,
        // height: 670,
        // drawOutOfBound: true, // 超出范围也显示出来，但形状就跟图片有些不一样了
        textStyle: {
          color: function () {
            return "rgb(" + [Math.round(Math.random() * 160), Math.round(Math.random() * 160), Math.round(Math.random() * 160)].join(",") + ")";
          },
        },
        emphasis: {
          textStyle: {
            shadowBlur: 10,
            shadowColor: "#333",
          },
        },
        maskImage: maskImage,
        data: data,
      },
    ],
  };

  maskImage.onload = function () {
    //   option.series[0].maskImage;
    chart.setOption(option);
  };

  // window.onresize = function () {
  //   chart.resize();
  // };
}
