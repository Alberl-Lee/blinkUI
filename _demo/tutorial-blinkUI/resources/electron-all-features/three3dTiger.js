import * as THREE from "./thirdparty/three/three.module.js";
import { OrbitControls } from "./thirdparty/three/OrbitControls.js";
import { SVGLoader } from "./thirdparty/three/SVGLoader.js";
import { GUI } from "./thirdparty/three/lil-gui.module.min.js";

export { three3dTiger };
var three3dTiger = {
  init: function () {
    init();
  },
};

let renderer, scene, camera, gui, guiData;

// init();

var widthContainer = window.innerWidth;
var heigthContainer = window.innerHeight;
widthContainer = 500;
heigthContainer = 500;

function init() {
  const container = document.getElementById("three3dTiger");

  //

  camera = new THREE.PerspectiveCamera(50, widthContainer / heigthContainer, 1, 1000);
  camera.position.set(0, 0, 200);

  //

  renderer = new THREE.WebGLRenderer({ antialias: true });
  renderer.setPixelRatio(window.devicePixelRatio);
  renderer.setSize(widthContainer, heigthContainer);
  renderer.outputEncoding = THREE.sRGBEncoding;
  container.appendChild(renderer.domElement);

  //

  const controls = new OrbitControls(camera, renderer.domElement);
  controls.addEventListener("change", render);
  controls.screenSpacePanning = true;

  //

  window.addEventListener("resize", onWindowResize);

  guiData = {
    currentURL: "assets/svg/three/tiger.svg",
    drawFillShapes: true,
    drawStrokes: true,
    fillShapesWireframe: false,
    strokesWireframe: false,
  };

  loadSVG(guiData.currentURL);

  createGUI();
}

function createGUI() {
  if (gui) gui.destroy();

  // gui = new GUI();
  var containerGUI = document.getElementById("three3dTigerUI");
  gui = new GUI({ container: containerGUI, width: 200 });

  gui
    .add(guiData, "currentURL", {
      Tiger: "assets/svg/three/tiger.svg",
      Hexagon: "assets/svg/three/hexagon.svg",
      Text: "assets/svg/three/tests/3.svg",
      "Style CSS inside defs": "assets/svg/three/style-css-inside-defs.svg",
      Defs: "assets/svg/three/tests/testDefs/Wave-defs.svg",
    })
    .name("SVG File")
    .onChange(update);

  gui.add(guiData, "drawStrokes").name("Draw strokes").onChange(update);

  gui.add(guiData, "drawFillShapes").name("Draw fill shapes").onChange(update);

  gui.add(guiData, "strokesWireframe").name("Wireframe strokes").onChange(update);

  gui.add(guiData, "fillShapesWireframe").name("Wireframe fill shapes").onChange(update);

  function update() {
    loadSVG(guiData.currentURL);
  }
}

function loadSVG(url) {
  //

  scene = new THREE.Scene();
  scene.background = new THREE.Color(0xb0b0b0);

  //

  const helper = new THREE.GridHelper(160, 10);
  helper.rotation.x = Math.PI / 2;
  scene.add(helper);

  //

  const loader = new SVGLoader();

  loader.load(url, function (data) {
    const paths = data.paths;

    const group = new THREE.Group();
    group.scale.multiplyScalar(0.25);
    group.position.x = -70;
    group.position.y = 70;
    group.scale.y *= -1;

    for (let i = 0; i < paths.length; i++) {
      const path = paths[i];

      const fillColor = path.userData.style.fill;
      if (guiData.drawFillShapes && fillColor !== undefined && fillColor !== "none") {
        const material = new THREE.MeshBasicMaterial({
          color: new THREE.Color().setStyle(fillColor).convertSRGBToLinear(),
          opacity: path.userData.style.fillOpacity,
          transparent: true,
          side: THREE.DoubleSide,
          depthWrite: false,
          wireframe: guiData.fillShapesWireframe,
        });

        const shapes = SVGLoader.createShapes(path);

        for (let j = 0; j < shapes.length; j++) {
          const shape = shapes[j];

          const geometry = new THREE.ShapeGeometry(shape);
          const mesh = new THREE.Mesh(geometry, material);

          group.add(mesh);
        }
      }

      const strokeColor = path.userData.style.stroke;

      if (guiData.drawStrokes && strokeColor !== undefined && strokeColor !== "none") {
        const material = new THREE.MeshBasicMaterial({
          color: new THREE.Color().setStyle(strokeColor).convertSRGBToLinear(),
          opacity: path.userData.style.strokeOpacity,
          transparent: true,
          side: THREE.DoubleSide,
          depthWrite: false,
          wireframe: guiData.strokesWireframe,
        });

        for (let j = 0, jl = path.subPaths.length; j < jl; j++) {
          const subPath = path.subPaths[j];

          const geometry = SVGLoader.pointsToStroke(subPath.getPoints(), path.userData.style);

          if (geometry) {
            const mesh = new THREE.Mesh(geometry, material);

            group.add(mesh);
          }
        }
      }
    }

    scene.add(group);

    render();
  });
}

function onWindowResize() {
  camera.aspect = widthContainer / heigthContainer;
  camera.updateProjectionMatrix();

  renderer.setSize(widthContainer, heigthContainer);
}

function render() {
  renderer.render(scene, camera);
}
